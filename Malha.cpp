#include <stdlib.h>                    // função rand
#include <time.h>                      //função time
#include <math.h>                      // operações matemáticas
#include <vector>
#include "Greedy.h"

using namespace std;



int main(){
	
	
	Malha malha1;
	Coord point;
	
	malha1.Adicionar_roteador_no_problema(2,7);
	malha1.Adicionar_roteador_no_problema(3,13);
	malha1.Adicionar_roteador_no_problema(5,17);	

   	malha1.Iniciar_Malha(0,100,0,100);

	malha1.Retirar_retangulo(30,70,-1,30);
	malha1.Retirar_retangulo(30,70,70,101);
	malha1.Retirar_retangulo(-1,30,30,70);
	malha1.Retirar_retangulo(70,101,30,70);

	/*malha1.Retirar_retangulo(0,30,0,14);
	malha1.Retirar_retangulo(0,14,14,23);
	malha1.Retirar_retangulo(0,4,23,37);
	malha1.Retirar_retangulo(0,14,37,67);
	malha1.Retirar_retangulo(0,14,83,115);
	malha1.Retirar_retangulo(0,4,115,129);
	malha1.Retirar_retangulo(0,14,129,138);
	malha1.Retirar_retangulo(0,30,138,152);
	malha1.Retirar_retangulo(30,44,0,4);
	malha1.Retirar_retangulo(44,59,0,14);
	malha1.Retirar_retangulo(75,90,0,14);
	malha1.Retirar_retangulo(90,104,0,4);
	malha1.Retirar_retangulo(104,145,0,14);
	malha1.Retirar_retangulo(30,44,148,152);
	malha1.Retirar_retangulo(44,59,138,152);
	malha1.Retirar_retangulo(75,90,138,152);
	malha1.Retirar_retangulo(90,104,148,152);
	malha1.Retirar_retangulo(104,145,138,152);
	malha1.Retirar_retangulo(120,145,14,23);
	malha1.Retirar_retangulo(120,145,129,138);
	malha1.Retirar_retangulo(120,145,46,106);
	malha1.Retirar_retangulo(26,108,26,126);*/

	/*malha1.Retirar_retangulo(0,144,0,20);
	malha1.Retirar_retangulo(0,144,132,152);
	malha1.Retirar_retangulo(0,20,0,152);
	malha1.Retirar_retangulo(124,144,0,152);*/
	
	//malha1.Saida_log();

	//malha1.Adicionar_roteador_no_ponto(4,1,1);




	
	while(malha1.Contagem_zero()!=true){
	point=malha1.Escolha_do_ponto();
	malha1.Adicionar_roteador_no_ponto(point.x,point.y,point.r);
	cout<<point.x<<" "<<point.y<<endl;	
		}
	malha1.Saida_teste();
	malha1.Saida_texto();
	
	malha1.Saida_log();
	
	return(0);
	}
