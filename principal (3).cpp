#include <iostream>
#include "biblioteca.hpp"
#include <locale.h>
#include <time.h>
using namespace std;

int main(){
    
    int tamanhoLivro = 10;
    Livro livros [tamanhoLivro];
    
    int tamanhoUsuario = 10;
    Usuario usuarios [tamanhoUsuario];
    
    Emprestimo emprestimos [10];
    
    time_t tempo;

    apresentarMenu(livros, usuarios, emprestimos, tamanhoLivro, tamanhoUsuario, tempo);

    
    

    return 0;
}
