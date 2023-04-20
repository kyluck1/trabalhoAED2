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
    
        
    temp* ocorr1 = ocorr1_;
    temp* ocorr2 = ocorr2_;

    int res = 0;
    if(ocorr1->dia == ocorr2->dia && ocorr1->mes == ocorr2->mes && ocorr1->ano == ocorr2->ano && ocorr1->hora == ocorr2->hora && ocorr1->minuto == ocorr2->minuto){
        res = 1;
    }
    return res;
    
}

void remover_ocorrencia_temperatura(t_lse* lista_temp){

    int dia_,mes_,ano_,hora_,min_;
    scanf("%d%d%d %d%d", &dia_,&mes_,&ano_,&hora_,&min_);
    temp* ocorrencia_;
    ocorrencia_->dia = dia_;
    ocorrencia_->mes=mes_;
    ocorrencia_->ano=ano_;
    ocorrencia_->hora = hora_;
    ocorrencia_->minuto = min_;

    temp* t;

    t = buscar_lse( lista_temp, ocorrencia_);
    if(t){
        imprimir_ocorrencia_temperatura(t);
        t = remover_lse(lista_temp, ocorrencia_);
    }

    if(t){
        imprimir_ocorrencia_temperatura(t);
        free(t);
    }
    
}

void imprimir_intervalo(t_lse* lista_temp, int x, int y){
    temp* ocorrencia_;
    
    for(int i=x;i<=y;i++){
        ocorrencia_ = acessar_lse(lista_temp,i);
        imprimir_ocorrencia_temperatura(ocorrencia_);
    }
}



int main(int argc, char const *argv[]){
    /*const int tipo = (int) argv[1][0]-48;
    const char* nome_arquivo = argv[2];
    FILE *arq = fopen(nome_arquivo, "r");
    fscanf(arq,<mascara>,<lista de variaveis>);

    */
   
   t_lse* ocorrencias_temperatura = criar_lse(imprimir_ocorrencia_temperatura,comparar_eventosTemp);

    int seq_,dia_, mes_, ano_,  hora_,  minuto_, radiacao_solar_;
    double temperatura_, umidade_relativa_;
   for(int i =0; i<2;i++ ){
        scanf("%d%d%d%d%d%d%d%lf%lf", &seq_, &dia_, &mes_, &ano_, &hora_, &minuto_, &radiacao_solar_, &temperatura_, &umidade_relativa_);
        temp* ocorrencia = cria_ocorrtem(seq_, dia_, mes_, ano_, hora_, minuto_, radiacao_solar_, temperatura_, umidade_relativa_);
        inserir_final_lse(ocorrencias_temperatura, ocorrencia);
   }

   imprimir_lse(ocorrencias_temperatura);

    remover_ocorrencia_temperatura(ocorrencias_temperatura);

    imprimir_lse(ocorrencias_temperatura);

}

