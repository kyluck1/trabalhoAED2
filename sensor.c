#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "listase.h"





typedef struct ocorrencia_temp temp;

struct ocorrencia_temp{
    int seq;
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int radiacao_solar;
    double temperatura;
    double umidade_relativa;
    int chave;
};

typedef struct ocorrencia_massadear vento;
struct ocorrencia_massadear{
    int seq;
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    double velocidade_media;
    double velocidade_instantanea;
    int direcao;
};


temp* cria_ocorrtem(int seq_, int dia_, int mes_, int ano_, int hora_, int minuto_, int radiacao_solar_, double temperatura_, double umidade_relativa_){

    temp* ocorrtemp = malloc(sizeof(temp));
    ocorrtemp->seq = seq_;
    ocorrtemp->dia = dia_;
    ocorrtemp->mes = mes_;
    ocorrtemp->ano = ano_;
    ocorrtemp->hora=hora_;
    ocorrtemp->minuto = minuto_;
    ocorrtemp->radiacao_solar = radiacao_solar_;
    ocorrtemp->temperatura = temperatura_;
    ocorrtemp-> umidade_relativa = umidade_relativa_;
    

    return ocorrtemp;
    

}

void imprimir_ocorrencia_temperatura(void* ocorrencia_){
    temp* ocorrencia = ocorrencia_;
    printf("%d %02d/%02d/%d %02d:%02d %d %.2lf %.2lf\n", ocorrencia-> seq, ocorrencia->dia, ocorrencia->mes, ocorrencia->ano, ocorrencia->hora, ocorrencia->minuto, ocorrencia->radiacao_solar, ocorrencia->temperatura, ocorrencia->umidade_relativa);

}



vento* cria_ocorrmassa(int seq_, int dia_, int mes_, int ano_, int hora_, int minuto_, double velocidade_media_, double velocidade_instantanea_, int direcao_){
    vento* ocorrmassa = malloc(sizeof(vento));
    ocorrmassa->seq = seq_;
    ocorrmassa->dia = dia_;
    ocorrmassa->mes = mes_;
    ocorrmassa->ano = ano_;
    ocorrmassa->hora = hora_;
    ocorrmassa->minuto = minuto_;
    ocorrmassa->velocidade_media = velocidade_media_;
    ocorrmassa->velocidade_instantanea = velocidade_instantanea_;
    ocorrmassa->direcao = direcao_; 

    return ocorrmassa;

}

void imprimir_ocorrencia_massa(void* ocorrencia_){
    vento* ocorrencia = ocorrencia_;

    printf("%d %02d/%02d/%d %02d:%02d %.2lf %.2lf %d\n", ocorrencia->seq, ocorrencia->dia, ocorrencia->mes, ocorrencia->ano, ocorrencia->hora, ocorrencia->minuto, ocorrencia->velocidade_media, ocorrencia->velocidade_instantanea, ocorrencia->direcao);

}
int comparar_eventosTemp(void* ocorr1_, void* ocorr2_){
    
        
    temp* ocorr1 = ocorr2_;
    temp* ocorr2 = ocorr1_;

    
    if(ocorr1->dia != ocorr2->dia){
        return -1;
    }else if(ocorr1->mes != ocorr2->mes){
        return -1;
    }else if(ocorr1->ano != ocorr2->ano){
        return -1;
    }else if(ocorr1->hora != ocorr2->hora){
        return -1;
    }else if(ocorr1->minuto != ocorr2->minuto){
        return -1;
    }

    return 1;
    
}

temp* remover_ocorrencia_temperatura(t_lse* lista_temp, int dia_, int mes_, int ano_,  int hora_,  int minuto_){

    
    temp* ocorrencia_;
    ocorrencia_->dia = dia_;
    ocorrencia_->mes = mes_;
    ocorrencia_->ano = ano_;
    ocorrencia_->hora = hora_;
    ocorrencia_->minuto = minuto_;
    

    temp* t;

    t = buscar_lse( lista_temp, ocorrencia_);
    imprimir_ocorrencia_temperatura(t);
    
    if(t){
        imprimir_ocorrencia_temperatura(t);
        t = remover_lse(lista_temp, ocorrencia_);
        free(t);
    }


}

void imprimir_intervalo(t_lse* lista_temp, int x, int y){
    temp* ocorrencia_;
    
    for(int i=x;i<=y;i++){
        
        ocorrencia_ = acessar_lse(lista_temp,i);
        if(ocorrencia_!= NULL){
            imprimir_ocorrencia_temperatura(ocorrencia_);
        }  
    }
}

temp* acessar_ocorrencia(t_lse* lista_temp, int x){
    temp* ocorrencia_;

    ocorrencia_ = acessar_lse(lista_temp,x);
    return ocorrencia_;
}

temp* buscar_ocorrencia(t_lse* lista_temp, int dia_, int mes_, int ano_, int hora_, int minuto_){

    temp* ocorrencia_;
    ocorrencia_->dia = dia_;
    ocorrencia_->mes = mes_;
    ocorrencia_->ano = ano_;
    ocorrencia_->hora = hora_;
    ocorrencia_->minuto = minuto_;

    temp* busca = buscar_lse(lista_temp, ocorrencia_);

    return busca;



}





int main(){
    /*const int tipo = (int) argv[1][0]-48;
    const char* nome_arquivo = argv[2];
    FILE *arq = fopen(nome_arquivo, "r");
    fscanf(arq,<mascara>,<lista de variaveis>);

    
   
   

    
   
   

   imprimir_lse(ocorrencias_temperatura);

    temp* temporaria = remover_ocorrencia_temperatura(ocorrencias_temperatura);

   // imprimir_lse(ocorrencias_temperatura);
    
    int n;
    scanf("%d", &n);

    temp* test2;

    test2 = acessar_ocorrencia(ocorrencias_temperatura, n);
    imprimir_ocorrencia_temperatura(test2);


    scanf("%d%d%d%d%d", &dia_, &mes_,&ano_,&hora_,&minuto_);

    test2 = buscar_ocorrencia(ocorrencias_temperatura, dia_,mes_,ano_,hora_,minuto_);
    imprimir_ocorrencia_temperatura(test2);

    */

    int seq_,dia_, mes_, ano_,  hora_,  minuto_, radiacao_solar_;
     double temperatura_, umidade_relativa_;
    t_lse* ocorrencias_temperatura = criar_lse(&imprimir_ocorrencia_temperatura,&comparar_eventosTemp);
    

    for(int i =0; i<10;i++ ){
        scanf("%d%d/%d/%d%d:%d%d%lf%lf", &seq_, &dia_, &mes_, &ano_, &hora_, &minuto_, &radiacao_solar_, &temperatura_, &umidade_relativa_);
        temp* ocorrencia = cria_ocorrtem(seq_, dia_, mes_, ano_, hora_, minuto_, radiacao_solar_, temperatura_, umidade_relativa_);
        inserir_final_lse(ocorrencias_temperatura, ocorrencia);
   }
   imprimir_lse(ocorrencias_temperatura);
    char opcao; 
    int pos;
    temp* temp_;
    vento* vent_;

    opcao = getchar();
    while(opcao != 'F'){
        
        if(opcao == 'R'){
            scanf("%d/%d/%d%d:%d", &dia_,&mes_, &ano_, &hora_, &minuto_);
            temp_ = buscar_ocorrencia(ocorrencias_temperatura,1, 7, 2022,  0,  1 );
            imprimir_ocorrencia_temperatura(temp_);
            temp_ = remover_ocorrencia_temperatura(ocorrencias_temperatura,dia_, mes_, ano_,  hora_,  minuto_ );
        
        }else if(opcao == 'A'){
            scanf("%d", &pos);
            temp_ = acessar_ocorrencia(ocorrencias_temperatura,pos);
            imprimir_ocorrencia_temperatura(temp_);

        }else if(opcao == 'B'){
           printf("Entrei\n");
           temp_ = buscar_ocorrencia(ocorrencias_temperatura, 1,7,2022,0,1);
           imprimir_ocorrencia_temperatura(temp_);
        }

       opcao = getchar();
    }
}
