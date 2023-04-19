#include "stdio.h"
#include "stdlib.h"
#include "string.h"




typedef struct lse t_lse;
typedef void(*t_imprimir_lse)(void*);

typedef int (*t_comparar_lse)(void* carga_na_lista, void* nova_carga);
t_lse* criar_lse(t_imprimir_lse impressora, t_comparar_lse comparar);

// operacoes baseadas em posicao
void inserir_inicio_lse(t_lse* lse, void* carga);
void* remover_inicio_lse(t_lse* lse);
void* acessar_lse(t_lse* lse, int pos);
void inserir_final_lse(t_lse* lse, void* carga);
void* remover_final_lse(t_lse* lse);
void imprimir_lse(t_lse* lse);
void* remover_lse(t_lse* lse, void* chave);
void* buscar_lse(t_lse* lse, void* chave);
void inserir_lse(t_lse* lse, void* carga);

/* Tipo elemento da LSE*/
typedef struct elem_lse t_elemento_lse;
struct elem_lse{
    void* cargautil;// carga util
    struct elem_lse* prox;// endereco prox
};

/**
 * cria um elemento da LSE
*/
t_elemento_lse* criar_elemento_lse(void* cargautil){
    t_elemento_lse* novo = malloc(sizeof(t_elemento_lse));
    novo->cargautil = cargautil;
    novo->prox = NULL;

    printf("Criando: %p %p %p\n", novo, novo->cargautil, novo->prox);

    return novo;
}

/**
 * Definição do tipo Lista Simplesmente Encadeada
*/
struct lse{
    t_elemento_lse* inicio; // Primeiro elemento
    int tamanho;
    t_imprimir_lse impressora; 
    t_comparar_lse comparar;
};

t_lse* criar_lse(t_imprimir_lse impressora, t_comparar_lse comparar){
     t_lse* nova;
     
    nova  = malloc(sizeof(t_lse));
    nova->inicio = NULL;
    nova->tamanho=0;
    nova->impressora = impressora;
    nova->comparar = comparar;

    return nova;
}

// operacoes baseadas em posicao
void inserir_inicio_lse(t_lse* lse, void* carga){
    
    t_elemento_lse* novo = criar_elemento_lse(carga);

    novo->prox = lse->inicio;
    lse->inicio = novo;
    lse->tamanho++;

}

void* remover_inicio_lse(t_lse* lse){
    void* carga=NULL;
    t_elemento_lse* removivel = lse->inicio;
    if (lse->inicio != NULL){    
        lse->inicio = removivel->prox;
        lse->tamanho--;
        carga = removivel->cargautil;

        free(removivel);
    }
    return carga;
}

void* acessar_lse(t_lse* lse, int pos){
    int i=1;
    void* carga=NULL; // entrada invalida
    if (pos<0){
        pos = (pos % lse->tamanho) + (lse->tamanho+1); 
        pos = (pos==0?1:pos);
    }else if(pos>0){
        pos = pos % lse->tamanho;
        pos = (pos==0?lse->tamanho:pos);
    }else{
        return carga;
    }

    t_elemento_lse* cam = lse->inicio;
    if ((pos<=lse->tamanho)){
        while(i<pos){
            cam = cam->prox;
            i++;
        }
        carga = cam->cargautil;
    }
    return carga;
}

void inserir_final_lse(t_lse* lse, void* carga){
    t_elemento_lse* novo = criar_elemento_lse(carga);
    if(lse->tamanho == 0){ // lse->inicio == NULL
        lse->inicio = novo;
    }else{
        t_elemento_lse* cam = lse->inicio;
        while(cam->prox!=NULL){
            cam=cam->prox;
        }
        cam->prox = novo;
    }
    lse->tamanho++;
}

void* remover_final_lse(t_lse* lse){
    void* carga=NULL;

    t_elemento_lse* ant=NULL;
    t_elemento_lse* cam=lse->inicio;
    if (lse->tamanho == 0){
        return carga;
    }else if(lse->tamanho == 1){
        cam = lse->inicio;
        lse->inicio=NULL;
    }else{
        while(cam->prox!=NULL){
            ant = cam;
            cam = cam->prox;
        }
        ant->prox = NULL;
    }
    carga = cam->cargautil;
    free(cam);
    lse->tamanho--;
    return carga;
}

void imprimir_lse(t_lse *lse){
    t_elemento_lse* cam = lse->inicio;
    while(cam!=NULL){
        lse->impressora(cam->cargautil);
        cam = cam->prox;
    } 
}

void inserir_lse(t_lse* lse, void* nova_carga){
    t_elemento_lse* cam = lse->inicio;
    t_elemento_lse* ant=NULL;

    lse->tamanho++;
    t_elemento_lse* novo = criar_elemento_lse(nova_carga);
    if (lse->inicio == NULL){ // lista vazia
       lse->inicio = novo;
    }else{
        while( (cam!=NULL) && (lse->comparar(cam->cargautil, nova_carga)<0)){
            ant = cam;
            cam = cam->prox;
        }
        // inicio
        if(cam == lse->inicio){
            novo->prox = cam;
            lse->inicio = novo;
        }else{
            ant->prox = novo;
            novo->prox = cam;
        }
    }
}

void* buscar_lse(t_lse* lse, void* chave){
    t_elemento_lse* cam=lse->inicio;

    while( (cam!=NULL) && (lse->comparar(cam->cargautil, chave)!=0)){
        cam = cam->prox;
    }
    if (cam != NULL)
        return cam->cargautil;
    else
        return NULL;
}

void* remover_lse(t_lse* lse, void* chave){
    t_elemento_lse* cam = lse->inicio;
    t_elemento_lse* ant = NULL;
    
    while( (cam!=NULL) && (lse->comparar(cam->cargautil , chave)!=0)){
        ant = cam;
        cam = cam->prox;
    }

    void* carga = NULL;
    if (cam != NULL){
        carga = cam->cargautil;
        if (cam == lse->inicio){ // inicio?
            lse->inicio = cam->prox;
        }else{
        ant->prox = cam->prox;
        }
        free(cam);
    }
    return carga; 

}

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

