#include <iostream>
#include <locale.h>
#include <time.h>
#include <limits>
#include "biblioteca.hpp"

void cadastroLivro(Livro livros [], int tamanhoLivro){
    
    string titulo, autor;
    int anoPublicacao, copias;
    
    
    cout<<"\n\n***** CADASTRO LIVRO *****"<<endl;
    cout<<"Digite o nome do livro: "<<endl;
    cin.ignore();
    getline(cin, titulo);
    cout<<"Digite o autor do livro: "<<endl;
    getline(cin, autor);
    cout<<"Digite o ano de publicação do livro: "<<endl;
    cin>>anoPublicacao;
    cout<<"Digite o numero de cópias: "<<endl;
    cin>>copias;
    
    Livro livro;
    livro.titulo = titulo;
    livro.autor = autor;
    livro.anoPublicacao = anoPublicacao;
    livro.copias = copias;
    livro.copiasDisponiveis = copias;
    
    for (int i=0; i<tamanhoLivro; i++){
        if (livros[i].titulo.empty()){
            livros[i]=livro;
            break;
        }
    }
    

}

void cadastroUsuario(Usuario usuarios [], int tamanhoUsuario ){
    
     string nome, id;
    
    cout<<"***** CADASTRO USUÁRIO *****"<<endl;
    cout<<"Digite o nome do usuario: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nome);
    cout<<"Digite o seu CPF/CNPJ"<<endl;
    cin>>id;
    
    verificarId(id);
    
    
    Usuario usuario;
    usuario.nome = nome;
    usuario.id=id;
    
    
    for (int i=0; i<tamanhoUsuario; i++){
        if (usuarios[i].nome.empty()){
            usuarios[i]=usuario;
            break;
        }
    }
    
}

void verificarId(string id){
    cout<<"Quantidade de caracteres:"<<id.size()<<endl;
    if(id.size() == 11 || id.size() == 14){
        return;
    }
    cout<<"CPF/CNPJ inválido"<<endl;
}

void emprestimoLivros(Livro livros[], Usuario usuarios[], Emprestimo emprestimos[], int tamanhoLivro, int tamanhoUsuario, time_t &tempo){
    
     Emprestimo emprestimo; 
     
     //buscar livros 
     int indiceLivro, indiceUsuario=-1; 
     bool livroValido = true;
     string tituloEmprestimo, idUsuario;
     
     cout<<"\n\n***** EMPRESTIMO LIVRO *****"<<endl;
     
     while(indiceUsuario < 0){
        cout<<"CPF/CNPJ do usuário: ";
        cin>>idUsuario;
        indiceUsuario = validarUsuario(tamanhoUsuario, usuarios, idUsuario);
     }
     
     
     
    emprestimo.id = idUsuario;
    emprestimo.dataEmprestimo = time(&tempo);
    
    cout<<"Título do livro: ";
    cin>>tituloEmprestimo;
    
    //verificar se temos esse livro cadastrado
    indiceLivro = validarLivro(tamanhoLivro, livros, tituloEmprestimo);
    emprestimo.titulo = tituloEmprestimo;
    
     //cópias disponíveis
     if (livros[indiceLivro].copiasDisponiveis > 0){
        cout<<"Empréstimo autorizado."<<endl;
        livros[indiceLivro].copiasDisponiveis --;
        livros[indiceLivro].quantidadeEmprestimos ++;
        usuarios[indiceUsuario].quantidadeEmprestimos ++;
         
        for (int i=0; i<10; i++){
            cout<<emprestimos[i].titulo<<endl;
            if (emprestimos[i].titulo.empty()){
                emprestimos[i]=emprestimo;
                
                cout<<"Emprestimo: \nId Pessoa; "<<emprestimos[i].id<<"\nTitulo: "<<emprestimos[i].titulo<<"\nData Emprestimo: "<<emprestimos[i].dataEmprestimo<<endl;
                break;
        }
    }
     } else {
         cout<<"Empréstimo não autorizado. Sem cópias disponíveis :("<<endl;
     }
     
}

int validarUsuario(int tamanhoUsuario, Usuario usuarios[], string idUsuario){
    bool usuarioValido = false;
    int indiceUsuario;
    
    for (int i=0; i<tamanhoUsuario; i++){
        if (idUsuario == usuarios[i].id){
            usuarioValido = true;
            indiceUsuario = i;
        }
    }
    
   if (!usuarioValido) {
        cout<<"\nUsuário não encontrado\n"<<endl;
        return -1;
    }
    return indiceUsuario;
}

int validarLivro( int tamanhoLivro, Livro livros[], string tituloEmprestimo){
    bool livroValido = false;
    int indiceLivro;
    
    for (int i=0; i<tamanhoLivro; i++){
       if (tituloEmprestimo == livros[i].titulo){
            livroValido = true;
            indiceLivro = i;
            cout<<"Livro está cadastrado em nosso sistema"<<endl;
        }
    }
    
    if (livroValido == false){
        cout<<"Livro não cadastrado :("<<endl;
        return 0;
    }
    return indiceLivro;
}

void devolucaoLivros(Livro livros[], Usuario usuarios[], Emprestimo emprestimos[], int tamanhoLivro, int tamanhoUsuario){
    
     
     int indiceLivro, indiceUsuario=-1; 
     bool usuarioValido = false, livroValido = true;
     string tituloEmprestimo, idUsuario;
     
     
     cout<<"\n\n***** DEVOLUÇÃO LIVRO *****"<<endl;
     while(indiceUsuario < 0){
        cout<<"CPF/CNPJ do usuário: ";
        cin>>idUsuario;
        indiceUsuario = validarUsuario(tamanhoUsuario, usuarios, idUsuario);
     }
    
    cout<<"Título do livro: ";
    cin>>tituloEmprestimo;
    
    //verificar se temos esse livro 
    indiceLivro = validarLivro(tamanhoLivro, livros, tituloEmprestimo);

     //cópias disponíveis
    livros[indiceLivro].copiasDisponiveis ++;
    
     
}

int pesquisaLivros(Livro livros [], int tamanhoLivro ){
    
    int tipoPesquisa=0, anoPesquisar, indiceLivro;
    string tituloPesquisar, autorPesquisar;
    bool livroValido=false;

    cout<<"\n\n***** PESQUISA DE LIVROS *****"<<endl;
    cout<<"Você gostaria de pesquisar por: \n1.Titulo\n2.Autor\n3.Ano publicação"<<endl;
    cin>>tipoPesquisa;
    
    if (tipoPesquisa == 1){
        cout<<"Titulo: ";
        cin>>tituloPesquisar;
        for (int i=0; i<tamanhoLivro; i++){
           if (tituloPesquisar == livros[i].titulo){
                livroValido = true;
                indiceLivro = i;
                cout<<"Titulo: " <<livros[i].titulo <<"\nAutor: "<<livros[i].autor<<"\nAno publicação: "<<livros[i].anoPublicacao<<"\nCópias: "<<livros[i].copias<<"\nCópias disponíveis: "<<livros[i].copiasDisponiveis<<"\n\n";
                break;
           } else  {
                livroValido = false;
            }
        }
        if (livroValido == false){
            cout<<" Livro não encontrado "<<endl;
        }
    } else if (tipoPesquisa == 2){
        cout<<"Autor : ";
        cin>>autorPesquisar;
        for (int i=0; i<tamanhoLivro; i++){
           if (autorPesquisar == livros[i].autor){
                livroValido = true;
                indiceLivro = i;
                cout<<"Titulo: " <<livros[i].titulo <<"\nAutor: "<<livros[i].autor<<"\nAno publicação: "<<livros[i].anoPublicacao<<"\nCópias: "<<livros[i].copias<<"\nCópias disponíveis: "<<livros[i].copiasDisponiveis<<"\n\n";
                break;
            } else  {
                livroValido = false;
            }
        }
        if (livroValido == false){
            cout<<" Livro não encontrado "<<endl;
        }
    } else if (tipoPesquisa == 3){
        cout<<" Ano de Publicação : ";
        cin>>anoPesquisar;
        for (int i=0; i<tamanhoLivro; i++){
           if (anoPesquisar == livros[i].anoPublicacao){
                livroValido = true;
                indiceLivro = i;
                cout<<"Titulo: " <<livros[i].titulo <<"\nAutor: "<<livros[i].autor<<"\nAno publicação: "<<livros[i].anoPublicacao<<"\nCópias: "<<livros[i].copias<<"\nCópias disponíveis: "<<livros[i].copiasDisponiveis<<"\n\n";
                break;
           } else  {
                livroValido = false;
            }
        }
        if (livroValido == false){
            cout<<" Livro não encontrado "<<endl;
        }
    } else {
         cout<<" Pesquisa não encontrada "<<endl;
    }
    
    return indiceLivro;
    /*
    switch(tipoPesquisa){
        
        case 1:
            cout<<"Titulo: ";
            cin>>tituloPesquisar;
            for (int i=0; i<tamanhoLivro; i++){
               if (tituloPesquisar == livros[i].titulo){
                    livroValido = true;
                    indiceLivro = i;
                    cout<<"Titulo: " <<livros[i].titulo <<"\nAutor: "<<livros[i].autor<<"\nAno publicação: "<<livros[i].anoPublicacao<<"\nCópias: "<<livros[i].copias<<"\nCópias disponíveis: "<<livros[i].copiasDisponiveis<<"\n\n";
                    break;
               } else  {
                    livroValido = false;
                }
            }
            if (livroValido == false){
                cout<<" Livro não encontrado "<<endl;
            }
            return indiceLivro;
        
         case 2:
            cout<<"Autor : ";
            cin>>autorPesquisar;
            for (int i=0; i<tamanhoLivro; i++){
               if (autorPesquisar == livros[i].autor){
                    livroValido = true;
                    indiceLivro = i;
                    cout<<"Titulo: " <<livros[i].titulo <<"\nAutor: "<<livros[i].autor<<"\nAno publicação: "<<livros[i].anoPublicacao<<"\nCópias: "<<livros[i].copias<<"\nCópias disponíveis: "<<livros[i].copiasDisponiveis<<"\n\n";
                    break;
                } else  {
                    livroValido = false;
                }
            }
            if (livroValido == false){
                cout<<" Livro não encontrado "<<endl;
            }
            return indiceLivro;
        case 3:
            cout<<" Ano de Publicação : ";
            cin>>anoPesquisar;
            for (int i=0; i<tamanhoLivro; i++){
               if (anoPesquisar == livros[i].anoPublicacao){
                    livroValido = true;
                    indiceLivro = i;
                    cout<<"Titulo: " <<livros[i].titulo <<"\nAutor: "<<livros[i].autor<<"\nAno publicação: "<<livros[i].anoPublicacao<<"\nCópias: "<<livros[i].copias<<"\nCópias disponíveis: "<<livros[i].copiasDisponiveis<<"\n\n";
                    break;
               } else  {
                    livroValido = false;
                }
            }
            if (livroValido == false){
                cout<<" Livro não encontrado "<<endl;
            }
            return indiceLivro;
        
        default:
            cout<<" Pesquisa não encontrada "<<endl;
            return 0;
    
    }
    */
    
    
}

int pesquisaLivrosPessoa(Emprestimo emprestimos [], Livro livros[], Usuario usuarios[], int tamanhoUsuario, int tamanhoLivro ){
    
    int i=0, indiceUsuario=-1;
    bool usuarioValido = false;
    string idUsuario;
    
    
     while(indiceUsuario < 0){
        cout<<"CPF/CNPJ do usuário: ";
        cin>>idUsuario;
        indiceUsuario = validarUsuario(tamanhoUsuario, usuarios, idUsuario);
     }
    
    for (int i=0; i<10; i++){
        if(emprestimos[i].id  == idUsuario){
            cout<<"Titulo livro:"<<emprestimos[i].titulo<<endl;
        }
    }
    return 0;
}

void listagemLivros(Livro livros [], int tamanhoLivro ){
    
    cout<<"**** LISTAGEM DE LIVROS DISPONÍVEIS ****"<<endl;
    for (int i=0; i<tamanhoLivro; i++){
        if (livros[i].copiasDisponiveis > 0){
            cout<<livros[i].titulo<<" - cópias disponíveis "<<livros[i].copiasDisponiveis<<endl;
        }
    }

}

void multaUsuario(Emprestimo emprestimos [], Usuario usuarios[], int tamanhoUsuario, time_t &tempo){
    
    int i=0, indiceUsuario=-1;
    bool usuarioValido = false;
    float multasTotais;
    string idUsuario;
    
    
     while(indiceUsuario < 0){
        cout<<"CPF/CNPJ do usuário: ";
        cin>>idUsuario;
        indiceUsuario = validarUsuario(tamanhoUsuario, usuarios, idUsuario);
     }
    
    /*
    for (int i=0; i<tamanhoUsuario; i++){
        if (numId == usuarios[i].id){
            usuarioValido = true;
            cout<<"Usuário válido";
        }
    }
    
    if (usuarioValido == false){
        cout<<"Usuário inválido";
    }
    */
    
    for (int i=0; i<10; i++){
        float multa=0;
        if(emprestimos[i].id  == idUsuario){
            float diferencaTempo = difftime(emprestimos[i].dataEmprestimo, time(&tempo));
            if (diferencaTempo > 604800){ // multa após 7 dias
                float quantDias = diferencaTempo / 86400;
                multa = quantDias;
            }
            //apresentar multas por livro
            if(multa > 0){
                cout<<emprestimos[i].titulo<<" - Multa R$"<<multa<<endl;
            } else {
                cout<<emprestimos[i].titulo<<" - Não possui multa"<<endl;
            }
            //somar multas 
            multasTotais = multasTotais + multa;
        }
    }
    
    /*
    while (emprestimos[i].id != 0){
        float multa=0;
        if(emprestimos[i].id  == numId){
            float diferencaTempo = difftime(emprestimos[i].dataEmprestimo, time(&tempo));
            if (diferencaTempo > 604800){ // multa após 7 dias
                float quantDias = diferencaTempo / 86400;
                multa = quantDias;
            }
            //apresentar multas por livro
            if(multa > 0){
                cout<<emprestimos[i].titulo<<" - Multa R$"<<multa<<endl;
            } else {
                cout<<emprestimos[i].titulo<<" - Não possui multa"<<endl;
            }
            //somar multas 
            multasTotais = multasTotais + multa;
        }
        i++;
    }
    */
    
    
}

void livrosPopulares(Livro livros[],  int tamanhoLivro){
    
    string tituloTop1 = livros[0].titulo, tituloTop2 = livros[0].titulo, tituloTop3 = livros[0].titulo;
    int top1 = livros[0].quantidadeEmprestimos, top2 = livros[0].quantidadeEmprestimos, top3 = livros[0].quantidadeEmprestimos;
    
    for (int i=0; i<tamanhoLivro; i++){
       if (livros[i].quantidadeEmprestimos > top1){
           tituloTop1 = livros[i].titulo;
       } else if (livros[i].quantidadeEmprestimos > top2){
           tituloTop2 = livros[i].titulo;
       } else if (livros[i].quantidadeEmprestimos > top3){
           tituloTop3 = livros[i].titulo;
       }
    }
    
    cout<<"Livros Destaque:\n\n TOP1 - "<<tituloTop1<<"\nTOP2 - "<<tituloTop2<<"\nTOP3 - "<<tituloTop3<<endl;
}

void usuariosPopulares(Usuario usuarios[],  int tamanhoUsuario){
    
    string nomeTop1 = usuarios[0].nome, nomeTop2 = usuarios[0].nome, nomeTop3 = usuarios[0].nome;
    int top1 = usuarios[0].quantidadeEmprestimos, top2 = usuarios[0].quantidadeEmprestimos, top3 = usuarios[0].quantidadeEmprestimos;
    
    for (int i=0; i<tamanhoUsuario; i++){
       if (usuarios[i].quantidadeEmprestimos > top1){
           nomeTop1 = usuarios[i].nome;
       } else if (usuarios[i].quantidadeEmprestimos > top2){
           nomeTop2 = usuarios[i].nome;
       } else if (usuarios[i].quantidadeEmprestimos > top3){
           nomeTop3 = usuarios[i].nome;
       }
    }
    
    cout<<"Usuários Destaque:\n\n TOP1 - "<<top1<<"\nTOP2 - "<<top2<<"\nTOP3 - "<<top3<<endl;
}

void apresentarRelatorio(Livro livros [], int tamanhoLivro, Usuario usuarios[],  int tamanhoUsuario){
    listagemLivros(livros, tamanhoLivro );
    livrosPopulares(livros, tamanhoLivro);
    usuariosPopulares(usuarios, tamanhoUsuario);
}

void apresentarMenu(Livro livros[], Usuario usuarios[], Emprestimo emprestimos[], int tamanhoLivro, int tamanhoUsuario, time_t &tempo){
    
    int opcao=1;
    while(opcao >=1 && opcao < 10){
        cout<<"\n\n***** BIBLIOTECA - MENU *****"<<endl;
        cout<<"01. Cadastro de livros"<<endl;
        cout<<"02. Cadastro de usuários"<<endl;
        cout<<"03. Empréstimos de livros"<<endl;
        cout<<"04. Devolução de livros"<<endl;
        cout<<"05. Pesquisa de livros"<<endl;
        cout<<"06. Pesquisa de livros por usuários / histórico"<<endl;
        cout<<"07. Listagem de livros disponíveis"<<endl;
        cout<<"08. Controle de multas"<<endl;
        cout<<"09. Relatório de estatisticas de uso"<<endl;
        cout<<"10. Encerrar programa"<<endl;
        cout<<"\nEscolha uma opção: "<<endl;
        cin>>opcao;
        
        switch(opcao){
            case 1: 
                cadastroLivro( livros, tamanhoLivro );
                break;
            case 2: 
                cadastroUsuario ( usuarios , tamanhoUsuario);
                break;
            case 3: 
                emprestimoLivros( livros, usuarios,  emprestimos, tamanhoLivro,  tamanhoUsuario, tempo);
                break;
             case 4:
                devolucaoLivros(livros, usuarios, emprestimos, tamanhoLivro, tamanhoUsuario);
                break;
            case 5:
                pesquisaLivros(livros, tamanhoLivro);
                opcao =5;
                break;
            case 6:
                pesquisaLivrosPessoa(emprestimos, livros, usuarios, tamanhoUsuario, tamanhoLivro);
                break;
            case 7:
                listagemLivros(livros, tamanhoLivro);
                break;
            case 8:
                multaUsuario(emprestimos, usuarios, tamanhoUsuario, tempo);
                break;
            case 9:
                apresentarRelatorio(livros, tamanhoLivro, usuarios, tamanhoUsuario);
                break;
            case 10:
                cout<<"Programa encerrado";
                break;
            
            default:
                cout << "Opção inválida! Tente novamente." << endl;
        }
    }
    
}



