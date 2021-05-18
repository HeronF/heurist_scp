#include <stdlib.h>                    // função rand
#include <time.h>                      //função time
#include <math.h>                      // operações matemáticas
#include <vector>
#include <fstream>
#include <iostream>

#define COL 70        //Definições usadas na Malha
#define LIN 70 

using namespace std;

struct Coord{
	int x,y,r;
	};

struct Pontos{
double fx,fy;            //coordenadas espaciais
bool atividade = true;  //Indicará se o ponto estará ativo ou inativo
bool sinal = false;     //indicará se o ponto está recebendo sinal
bool roteador = false;  //indicará se o ponto está com um roteador alocado
int tipo_rot =-1;       //tipo de roteador alocado, -1 indica nenhum
};

class Malha{
public:

vector<float> retangulo_retirado[4];

vector<float> roteador[2]; 									//0 custo, 1 raio

double dx,dy;

struct Pontos malha[LIN][COL];

void Iniciar_Malha(float Xi, float Xf, float Yi, float Yf); //inicia malha com dimensões 
void Saida_teste();											//saida pequena em texto para checar coesão
void Saida_texto();		
void Retirar_retangulo(float Xi,float Xf,float Yi,float Yf);//retira pontos de atividade
void Adicionar_roteador_no_problema(float custo, float raio);
void Adicionar_roteador_no_ponto(int x, int y, int r);				//Adiciona um roteador no ponto x,y
Coord Escolha_do_ponto();
bool Contagem_zero();
void Saida_log();
int Contagem_H();

};


void Malha::Iniciar_Malha(float Xi, float Xf, float Yi, float Yf){	
	
dx=(Xf-Xi)/(float)(COL);
dy=(Yf-Yi)/(float)(LIN);

for(int i=0; i<LIN; i++){
    for(int j=0; j<COL; j++){
        malha[i][j].fx = Xi+i*dx;
        malha[i][j].fy = Yi+j*dy;
        }
    }

return;
}

void Malha::Saida_teste(){

ofstream saida_texto_arq("Saida.txt");
if(saida_texto_arq.is_open()){

for(int i=0; i<LIN; i++){
    for(int j=0;j<COL;j++){
        int a=0;
        if(malha[i][j].atividade==true) a=1;
        saida_texto_arq << a << " ";
    }
    saida_texto_arq << endl;
}
for(int i=1;i<5;i++){
    saida_texto_arq << endl;
}
for(int i=0; i<LIN; i++){
    for(int j=0;j<COL;j++){
        int a=0;
        if(malha[i][j].sinal==1) a=1;
        saida_texto_arq << a << " ";
    }
    saida_texto_arq << endl;
}
for(int i=1;i<5;i++){
    saida_texto_arq << endl;
}
for(int i=0; i<LIN; i++){
    for(int j=0;j<COL;j++){
        int a=0;
        if(malha[i][j].roteador==1) a=1;
        saida_texto_arq << a << " ";
    }
    saida_texto_arq << endl;
}

saida_texto_arq.close();


}
return;
}

void Malha::Retirar_retangulo(float Xi,float Xf,float Yi,float Yf){
	
retangulo_retirado[0].push_back(Xi);
retangulo_retirado[1].push_back(Xf);
retangulo_retirado[2].push_back(Yi);
retangulo_retirado[3].push_back(Yf);
	for(int i=0; i<LIN; i++){
		for(int j=0;j<COL;j++){
			
			if((malha[i][j].fx>=Xi)&&(malha[i][j].fx<=Xf)&&(malha[i][j].fy>=Yi)&&(malha[i][j].fy<=Yf))	malha[i][j].atividade=false;
			
		}
	}
return;
}

void Malha::Adicionar_roteador_no_problema(float custo, float raio){
	roteador[0].push_back(custo);
	roteador[1].push_back(raio);
	
	return;
	}

void Malha::Adicionar_roteador_no_ponto(int x, int y,int r){
	malha[x][y].roteador = true;
	malha[x][y].tipo_rot = r;
	int value[2];
	value[0]=ceil(roteador[1][r]/dx);
	value[1]=ceil(roteador[1][r]/dy);
	for(int i=fmax((x-value[0]-1),0); i<fmin((x+value[0]+1),LIN); i++){
		for(int j=fmax((y-value[1]-1),0);j<fmin((y+value[1]+1),COL);j++){
			if((malha[x][y].fx-malha[i][j].fx)*(malha[x][y].fx-malha[i][j].fx)+(malha[x][y].fy-malha[i][j].fy)*(malha[x][y].fy-malha[i][j].fy)<roteador[1][r]*roteador[1][r]){
			malha[i][j].sinal=true;
			}
		}
	}


	return;
	}	
	
Coord Malha::Escolha_do_ponto(){
	srand (time(NULL));
	vector<Coord> pont;
	float peso, melhor_peso=0;
	int value[2][roteador[0].size()];
	
	for(int i=0;i<roteador[0].size();i++){
		value[0][i]=ceil(roteador[1][i]/dx);
		value[1][i]=ceil(roteador[1][i]/dy);
		}
	for(int r=0;r<roteador[1].size();r++){
		for(int ii=0;ii<LIN; ii++){
			for(int jj=0; jj<COL; jj++){
				if((malha[ii][jj].atividade==true)&&(malha[ii][jj].sinal==false)){
					int qnt=0;
                  /*  for(int i=0; i<LIN; i++){
						for(int j=0;j<COL;j++){
								if(((malha[ii][jj].fx-malha[i][j].fx)*(malha[ii][jj].fx-malha[i][j].fx)+(malha[ii][jj].fy-malha[i][j].fy)*(malha[ii][jj].fy-malha[i][j].fy)<roteador[1][r]*roteador[1][r])&&(malha[i][j].sinal==false)&&(malha[i][j].atividade==true)){
									qnt++;
								}
							}
						}*/
					for(int i=fmax((ii-value[0][r]),0); i<fmin((ii+value[0][r]),LIN); i++){
						for(int j=fmax((jj-value[1][r]),0);j<fmin((jj+value[1][r]),COL);j++){
								if(((malha[ii][jj].fx-malha[i][j].fx)*(malha[ii][jj].fx-malha[i][j].fx)+(malha[ii][jj].fy-malha[i][j].fy)*(malha[ii][jj].fy-malha[i][j].fy)<roteador[1][r]*roteador[1][r])&&(malha[i][j].sinal==false)&&(malha[i][j].atividade==true)){
									qnt++;
								}
							}
						}
					peso = qnt/roteador[0][r];
					if(peso>melhor_peso){
						melhor_peso=peso;
						pont.clear();
						Coord pont_apoio;
						pont_apoio.x=ii;
						pont_apoio.y=jj;
						pont_apoio.r=r;
						pont.push_back(pont_apoio);
                        cout << "maior" << endl;
						}
					else if(!(peso-melhor_peso>0)&&!(peso-melhor_peso<0)){
						Coord pont_apoio;
						pont_apoio.x=ii;
						pont_apoio.y=jj;
						pont_apoio.r=r;
						pont.push_back(pont_apoio);
                        cout << "igual" << endl;
						}	
					}
				}
			}
		}
	int saida = rand()%pont.size();	
	return(pont[saida]);
	}
	
bool Malha::Contagem_zero(){
	int a=0;
	for(int i=0; i<LIN; i++){
		for(int j=0; j<COL; j++){
			if((malha[i][j].sinal==false)&&(malha[i][j].atividade==true)) return(false);
        }
    }
	return(true);
	}

void Malha::Saida_log(){
	ofstream log("logResultados.txt",ios::app);
	static bool uso=false;
	if(uso==false){
	if(log.is_open()){
		int b= Contagem_H();
		log <<"Numero d (máximo de elementos em um único conjunto):" << b << endl;
		double a=0;
		for(int j=1;j<b+1;j++)a=a+(1/(double)j);
		log <<"que resulta em H(d):"<< a << endl;
		uso=true;
		}
	log.close();
	}
	else{
		float custo=0;
		for(int i=0; i<LIN;i++){
		for(int j=0; j<COL; j++){
			if(malha[i][j].roteador==true){
				custo+=roteador[0][malha[i][j].tipo_rot];
				log <<" x: " << malha[i][j].fx <<  ". y:" << malha[i][j].fy << ". tipo:" << malha[i][j].tipo_rot << "(custo,raio): (" << roteador[0][malha[i][j].tipo_rot] << "," << roteador[1][malha[i][j].tipo_rot] << ")" << endl;
				}
			}
		}
		log << "custo total:" << custo << endl;
		log.close();
		}
	return;
	}
	
int Malha::Contagem_H(){
	int maior_a=0,a=0;
	int maior_raio=0, r;
	int value[2];
	
	for(int i=0;i<roteador[1].size();i++){
		if(roteador[1][i]>maior_raio){
			maior_raio=roteador[1][i];
			r=i;			
			}
		}
	value[0]=ceil(roteador[1][r]/dx);
	value[1]=ceil(roteador[1][r]/dy);
		
	for(int ii=0;ii<LIN; ii++){
		for(int jj=0; jj<COL; jj++){
			if((malha[ii][jj].atividade==true)&&(malha[ii][jj].sinal==false)){
				int qnt=0;
				for(int i=fmax((ii-value[0]),0); i<fmin((ii+value[0]+1),LIN); i++){
					for(int j=fmax((jj-value[1]),0);j<fmin((jj+value[1]+1),COL);j++){
							if(((malha[ii][jj].fx-malha[i][j].fx)*(malha[ii][jj].fx-malha[i][j].fx)+(malha[ii][jj].fy-malha[i][j].fy)*(malha[ii][jj].fy-malha[i][j].fy)<=roteador[1][r]*roteador[1][r])&&(malha[i][j].sinal==false)&&(malha[i][j].atividade==true)){
								qnt++;
							}
						}
					}
				a=qnt;
				if(a>maior_a)maior_a=a;
				}
			}
		}
	return(a);
	}

void Malha::Saida_texto(){
	ofstream arq("Saida_dados.txt");
	
	vector<Coord> lista_roteadores;
	
		for(int i=0; i<LIN;i++){
		for(int j=0; j<COL; j++){
			Coord apoio;
			if(malha[i][j].roteador==true){
				apoio.x=i;
				apoio.y=j;
				apoio.r=malha[i][j].tipo_rot;
				lista_roteadores.push_back(apoio);
				}
			}
		}
		
	float tamanho_malha[4];
	
	tamanho_malha[0]=malha[0][0].fx;
	tamanho_malha[1]=malha[LIN-1][0].fx+dx;
	tamanho_malha[2]=malha[0][0].fy;
	tamanho_malha[3]=malha[0][COL-1].fy+dy;
	
	if(arq.is_open()){	
		arq << LIN << "\n" << COL << endl;
		
		for(int i = 0; i<4; i++) arq << tamanho_malha[i] << endl;		
		
		arq << retangulo_retirado[0].size() << endl;
		cout << "retangulo retirado" << retangulo_retirado[0].size() << endl;
		for(int i=0;i<retangulo_retirado[0].size();i++) arq << retangulo_retirado[0][i] << "\n" << retangulo_retirado[1][i] << "\n" << retangulo_retirado[2][i] << "\n" << retangulo_retirado[3][i] << endl;
		
		arq << roteador[1].size() << endl;
		cout << "tipos roteadores" << roteador[1].size() << endl;
		for(int i=0;i<roteador[1].size();i++) arq << roteador[0][i] << "\n" << roteador[1][i] << endl;
		
		arq << lista_roteadores.size() << endl;
		for(int i=0;i<lista_roteadores.size(); i++){ arq << lista_roteadores[i].x << "\n" << lista_roteadores[i].y << "\n" << lista_roteadores[i].r << endl;
	
}
	arq.close();	
}

	return;
	}		
