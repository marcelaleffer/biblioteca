#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP
using namespace std;

struct Livro{
    string titulo;
    string autor;
    int anoPublicacao;
    int copias;
    int copiasDisponiveis=0;
    int quantidadeEmprestimos=0;
};

struct Usuario{
    string nome;
    string id;
    Livro livros [10];
    int quantidadeEmprestimos=0;
    
};

struct Emprestimo {
    string id; 
    string titulo;
    int dataEmprestimo;
};


void cadastroLivro(Livro livros [], int tamanhoLivro );
void cadastroUsuario(Usuario usuarios[], int tamanhoUsuario );
void verificarId(string id);
void emprestimoLivros(Livro livros[], Usuario usuarios[], Emprestimo emprestimos[], int tamanhoLivro, int tamanhoUsuario, time_t &tempo);
int validarUsuario(int tamanhoUsuario, Usuario usuarios[], string idUsuario);
int validarLivro( int tamanhoLivro, Livro livros[], string tituloEmprestimo);
void devolucaoLivros(Livro livros[], Usuario usuarios[], Emprestimo emprestimos[], int tamanhoLivro, int tamanhoUsuario);
int pesquisaLivros(Livro livros [], int tamanhoLivro );
int pesquisaLivrosPessoa(Emprestimo emprestimos [], Livro livros[], Usuario usuarios[], int tamanhoUsuario, int tamanhoLivro );
void listagemLivros(Livro livros [], int tamanhoLivro );
void multaUsuario(Emprestimo emprestimos [], Usuario usuarios[], int tamanhoUsuario, time_t &tempo);
void livrosPopulares(Livro livros[],  int tamanhoLivro);
void usuariosPopulares(Usuario usuarios[],  int tamanhoUsuario);
void apresentarRelatorio(Livro livros [], int tamanhoLivro, Usuario usuarios[], int tamanhoUsuario);
void apresentarMenu(Livro livros[], Usuario usuarios[], Emprestimo emprestimos[], int tamanhoLivro, int tamanhoUsuario, time_t &tempo);

#endif
