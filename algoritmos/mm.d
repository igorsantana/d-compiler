import std.stdio;

void main(string[ ] args){
    int m, n , q = 0;
    int matrizA[50][50];
    int matrizB[50][50];
    int matrizC[50][50]; //matriz resultante
    
    writeln("*** Multiplicacao de matriz de ordem maxima 50 ***");
    
    writeln("Quantidade de linhas da Matriz A: ");
    scanf("%i", &m);
    
    writeln("Quantidade de colunas da Matriz A / linhas da Matriz B: ");
    scanf("%i", &n);
    
    writeln("Quantidade de colunas da Matriz B: ");
    scanf("%i", &q);
   
    writeln("Matriz A: ", m,"x",n, "\n", "Matriz B: ", n,"x",q);
    
    writeln("Preencha a matriz A:");
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            writeln("MatrizA[",i,"]","[",j,"]");
            scanf("%i", &matrizA[i][j]);
        }
    }
    
    writeln("----------------------------------");
    
    writeln("Preencha a matriz B:");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < q; j++){
            writeln("MatrizB[",i,"]","[",j,"]");
            scanf("%i", &matrizB[i][j]);
        }
    }
    
    int somaProduto = 0;
    for(int c = 0; c < m; c++){
        for(int b = 0; b < q; b++){
            somaProduto = 0;        
            for(int j = 0; j < n; j++){
                somaProduto = somaProduto + (matrizA[c][j] * matrizB[j][b]);
            }
            matrizC[c][b] = somaProduto;
        }
    }
    
    writeln("----------------------------------");
    
    writeln("Resultado: Matriz [",m,"][",q,"]");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < q; j++){
            write(matrizC[i][j], "\t");
        }
            writeln("\n");
    }
}
