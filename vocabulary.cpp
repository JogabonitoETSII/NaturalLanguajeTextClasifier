#include "vocabulary.hpp"


Vocabulary::Vocabulary () {}

int Vocabulary::parseFile (string fileName) {
	if (checkFileExist (fileName)) {
		string currentLine;// cambie el vector de string words a atributo privado de clase
		//por que lo necesitaremos para crear las partes de esta semana
		int wordCounter = 0;
	
		while (std::getline(file, currentLine)) {			
			currentLine = currentLine.substr(6, currentLine.size() - 1);			
			istringstream flux(currentLine);
    	string token;      
    	while (flux >> token) {
    		
   
    		if((!regex_match(token,textHastag_)) && (!regex_match(token,textLink_))&& (!regex_match(token,textSpecials))
    			&& (!regex_match(token,textPerson)) 	&& (!regex_match(token,textSinbol)) && (!regex_match(token,textExclamation))
    					&& (!regex_match(token,textAmpersan)) ){
	    		words.push_back(token);
	    		wordCounter++;
    		}
    	}
    }
    sort( words.begin() , words.end() );// ordenamos alfabeticamente
    words=dontWordRepeat();// quitamos las repetidas
    ofstream outFile (OUT_FILE);
    
    outFile << WORD_NUMBER << words.size() << endl;//metemos los datos en el fichero
    for (string word : words) {
      outFile << WORD << word << endl;
    }
    outFile.close();
    file.close();
    return 0;
	}else{
		return ERROR_OPEN_FILE;
	}
}

bool Vocabulary::checkFileExist (string fileName) {
	file.open (fileName);
	if (file.is_open()) {
		return true;	
	}
	else{
		return false;
	}
}

vector<string> Vocabulary::dontWordRepeat(){
	vector<string> DontWordRepeatAux;
	int j=1;
	int k=0;
	int countWordEq=0;
	DontWordRepeatAux.push_back(words[0]);
	for(int i=0;i<words.size()-1;i++){
			if((words[i].size()!=words[i + 1 ].size()) && (words[i].compare(0,words[i+1].size(),words[i+1]) != 0 )){
 				DontWordRepeatAux.push_back(words[i+1]);
			}
			else{
					if( words[i].compare(words[i+1]) != 0 ){// si la cantidad de caracteres acertas es distinta de la primera palabra no es repetida
						 DontWordRepeatAux.push_back(words[i+1]);///por lo tanto se suma al corpus
					}
			}
	}
	return DontWordRepeatAux;
}


int Vocabulary::learning(string input, string output){
		vector<string> learnWords;
		int countLine=0;
		if (checkFileExist (input.c_str())) {
		string currentLine;// cambie el vector de string words a atributo privado de clase
		//por que lo necesitaremos para crear las partes de esta semana
			while (std::getline(file, currentLine)) {			
				currentLine = currentLine.substr(6, currentLine.size() - 1);			
				istringstream flux(currentLine);
		    	string token;      
		    	countLine++;
		    	while(flux>>token){
		    			if((!regex_match(token,textHastag_)) && (!regex_match(token,textLink_))&& (!regex_match(token,textSpecials))
    					&& (!regex_match(token,textPerson)) 	&& (!regex_match(token,textSinbol)) && (!regex_match(token,textExclamation))
    					&& (!regex_match(token,textAmpersan)) ){
	    					learnWords.push_back(token);
    					}
		    	}
			}
			
	ofstream outFile (output.c_str());
	cout << learnWords.size()<<endl;
    outFile << "Documentos" << countLine << endl;//metemos los datos en el
    outFile << WORD_NUMBER << learnWords.size() << endl;//metemos los datos en el 
    float j=0;
    float frec_=0;
    float prob=0;
     
    for (string word : words) {
  		frec_=countWordsAppear(learnWords,j);
    	if(frec_==0){
    		prob=log(((frec_+1)/(words.size()+learnWords.size()+1)));
	      outFile << WORD << word << " " << frec_+1<< " " << prob <<endl;
    	}
    	else{
    		prob=log(((frec_+1)/(words.size()+learnWords.size()+1)));
        outFile << WORD << word << " " << frec_<< " " << prob <<endl;
    	}
      j++;
      prob=0;
      frec_=0;
    }
    	file.close();
		learnWords.empty();	
			outFile.close();
			return 0;
		}else{
		return ERROR_OPEN_FILE;
		}
}

void Vocabulary::classifyRelNoRelText(string text , string rel , string notRel){
	words.empty();
	Evaluator aux;
	vector<Evaluator> evalRel;
	std::vector<Evaluator> evalNotRel ;
	string token="";
	int trash;
	float fluxProbability=0;
	int fluxFrecuency=0;
	if (checkFileExist (rel)) {
		string currentLine;// cambie el vector de string words a atributo privado de clase
		//por que lo necesitaremos para crear las partes de esta semana
		int wordCounter = 0;
		while (std::getline(file, currentLine)) {			
			currentLine = currentLine.substr(8, currentLine.size() - 1);
			istringstream flux(currentLine);
			flux >> token;
			flux >>fluxFrecuency;
			flux >> fluxProbability;
			aux.setProbability(fluxProbability);
			aux.setWord(token);
			evalRel.push_back(aux);
		}
	}
	file.close();
	if (checkFileExist (notRel)) {
		string currentLine;// cambie el vector de string words a atributo privado de clase
		//por que lo necesitaremos para crear las partes de esta semana
		int wordCounter = 0;
		while (std::getline(file, currentLine)) {			
			currentLine = currentLine.substr(8, currentLine.size() - 1);
			istringstream flux(currentLine);
			flux >> token;
			flux >>fluxFrecuency;
			flux >> fluxProbability;
			aux.setProbability(fluxProbability);
			aux.setWord(token);
			evalNotRel.push_back(aux);
			
		}
	}
	file.close();
	if (checkFileExist (text)) {
		ofstream outFile ("clasificasion.txt");
		string currentLine;// cambie el vector de string words a atributo privado de clase
		//por que lo necesitaremos para crear las partes de esta semana
		float probabilityAcumulateForWordRelevant=0;
		float probabilityAcumulateForWordNotRelevant=0;
		int rel=0;
		int norel=0;
		float relevante=(4654/10806);
		float norelevante=(6152/10808);
		while (std::getline(file, currentLine)) {			
			currentLine = currentLine.substr(6, currentLine.size() - 1);			
			istringstream flux(currentLine);
	    	string token;    
	    	probabilityAcumulateForWordNotRelevant=norelevante;
	    	probabilityAcumulateForWordRelevant=relevante;
	    	while (flux >> token) {
	    		//Buscamos la probabilidad en los relevantes
	    		 for (int i = 0;i < evalRel.size() ; i++ ){
	    		 	if(evalRel[i].getWord().compare(token) == 0){
	    		 		probabilityAcumulateForWordRelevant+=evalRel[i].getProbability();
	    		 	
	    		 	}
	    		 }
	    		 	
	    		 // buscamos la probabilidad con los no relevantes
	    		 for (int i = 0; i < evalNotRel.size(); i++){
	    		 	if(evalNotRel[i].getWord().compare(token) == 0){
	    		 		probabilityAcumulateForWordNotRelevant+=evalNotRel[i].getProbability();
	    		 		
	    		 	}
	    		 }
	    
	    	}
	    	if(probabilityAcumulateForWordRelevant < probabilityAcumulateForWordNotRelevant){
	    		norel++;
	    		 	outFile <<"NoRelevante: "<< currentLine <<endl;
	    	}
	    	else{
	    		rel++;
	    		 	outFile <<"Relevante:"<< currentLine <<endl;
	    		 	
	    	}
	    	probabilityAcumulateForWordRelevant=0;
	    	probabilityAcumulateForWordNotRelevant=0;
		}
		cout << " Relevantes -> "<< rel << "   NoRelevantes ->  "<<  norel << endl;
		outFile.close();
		file.close();
	}
	
}




float Vocabulary::countWordsAppear(vector<string> learnWords,int j){
		float frec=0;
		for(int i=0;i<learnWords.size();i++){
			  	if(words[j].compare(learnWords[i])==0){
			  		frec++;
			  	}
		}	  
		return frec;
}
void Vocabulary::checkPorcentlyEfectivity(string fileName){
	int count=0;
	int countline=0;
	float resultado=0;
	if(checkFileExist("clasificasion.txt")){
	string currentLine;
		while(std::getline(file,currentLine)){
			if((countline<4654) && (regex_match(currentLine,textRelevante))){
				count++;
			}
			else if((countline>=4654) && (regex_match(currentLine,textNoRelevante))){
				count++;
			}
			countline++;
		}
	
		 resultado=count/(countline);
		cout << "porcentaje de acierto -> "<< count <<"   "<< countline << "   " <<resultado<<endl;
	}
	ofstream f(fileName.c_str());
	f << resultado*100<< endl;
	f.close();
	file.close();
}


Vocabulary::~Vocabulary() {
	words.empty();
}