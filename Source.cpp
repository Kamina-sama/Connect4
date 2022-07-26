#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<ctime>
//esse código só funciona no Windows, eu precisei usar da API dele na função print para deixar o texto colorido
//(senão fica extremamente confuso de se jogar)
#include<Windows.h>
using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::endl;

unsigned board[42];//42=6 rows*7 columns

inline void reset() {
	for (auto i = 0; i < 42; ++i) board[i] = 0;
}

inline bool win(short player) {
	//check rows for horizontal win
	for (size_t i = 0; i < 42; i += 7) {
		for (size_t j = 0; j <= 3; ++j) if (board[i + j] == player && board[i + j + 1] == player && board[i + j + 2] == player && board[i + j + 3] == player) {
			return true;
		}
	}
	//check columns for vertical win
	for (size_t i = 0; i < 7; ++i) {
		for (size_t j = 0; j <= 14; j += 7) if (board[i + j] == player && board[i + j + 7] == player && board[i + j + 14] == player && board[i + j + 21] == player) {
			return true;
		}
	}
	//check for diagonal victory
	for (size_t i = 3; i <= 17; i += 7) {
		for (size_t j = 0; j <= 3; ++j) {
			if (board[i + j] == player && board[i + j + 6] == player && board[i + j + 12] == player && board[i + j + 18] == player) return true;
			if (board[i - j] == player && board[i - j + 8] == player && board[i - j + 16] == player && board[i - j + 24] == player) return true;
		}

	}
	return false;
}
inline bool win(const std::vector<unsigned>& board, short player) {
	//check rows for horizontal win
	for (size_t i = 0; i < 42; i += 7) {
		for (size_t j = 0; j <= 3; ++j) if (board[i + j] == player && board[i + j + 1] == player && board[i + j + 2] == player && board[i + j + 3] == player) {
			return true;
		}
	}
	//check columns for vertical win
	for (size_t i = 0; i < 7; ++i) {
		for (size_t j = 0; j <= 14; j += 7) if (board[i + j] == player && board[i + j + 7] == player && board[i + j + 14] == player && board[i + j + 21] == player) {
			return true;
		}
	}
	//check for diagonal victory
	for (size_t i = 3; i <= 17; i += 7) {
		for (size_t j = 0; j <= 3; ++j) {
			if (board[i + j] == player && board[i + j + 6] == player && board[i + j + 12] == player && board[i + j + 18] == player) return true;
			if (board[i - j] == player && board[i - j + 8] == player && board[i - j + 16] == player && board[i - j + 24] == player) return true;
		}

	}
	return false;
}

//função heuristica para algoritmo minimax: esta perto de ganhar se tiver houver 3 peças consecutivas com espaço para uma quarta
//ou algo do tipo XPXPX onde P é uma peça e X é um espaço vazio (colocar uma peça no meio faz com que o oponente seja incapaz de defender os dois lados)
inline bool closetowin(short player) {
	for (size_t i = 0; i < 42; i += 7) {
		for (size_t j = 0; j <= 3; ++j) if (board[i + j] == 0 && board[i + j + 1] == player && board[i + j + 2] == player && board[i + j + 3] == 0) {
			return true;
		}
		for (size_t j = 0; j <= 2; ++j) if (board[i + j] == 0 && board[i + j + 1] == player && board[i + j + 2] == 0 && board[i + j + 3] == player && board[i + j + 4] == 0) {
			return true;
		}
	}
	for (size_t i = 0; i < 7; ++i) {
		for (size_t j = 0; j <= 14; j += 7) if (board[i + j] == 0 && board[i + j + 7] == player && board[i + j + 14] == player && board[i + j + 21] == player) {
			return true;
		}
	}
	//diagonals
	for (size_t i = 10; i <= 17; i += 7) {
		for (size_t j = 0; j <= 3; ++j) {
			if (board[i + j] == player && board[i + j + 6] == player && board[i + j + 12] == player && board[i + j + 18] == 0) return true;
			if (board[i + j] == player && board[i + j + 6] == player && board[i + j + 12] == 0 && board[i + j + 18] == player) return true;
			if (board[i + j] == player && board[i + j + 6] == 0 && board[i + j + 12] == player && board[i + j + 18] == player) return true;
			if (board[i + j] == 0 && board[i + j + 6] == player && board[i + j + 12] == player && board[i + j + 18] == player) return true;

			if (board[i - j] == player && board[i - j + 8] == player && board[i - j + 16] == player && board[i - j + 24] == 0) return true;
			if (board[i - j] == player && board[i - j + 8] == player && board[i - j + 16] == 0 && board[i - j + 24] == player) return true;
			if (board[i - j] == player && board[i - j + 8] == 0 && board[i - j + 16] == player && board[i - j + 24] == player) return true;
			if (board[i - j] == 0 && board[i - j + 8] == player && board[i - j + 16] == player && board[i - j + 24] == player) return true;
		}

	}
	return false;
}
inline bool closetowin(const std::vector<unsigned> board, short player) {
	for (size_t i = 0; i < 42; i += 7) {
		for (size_t j = 0; j <= 3; ++j) if (board[i + j] == 0 && board[i + j + 1] == player && board[i + j + 2] == player && board[i + j + 3] == 0) {
			return true;
		}
		for (size_t j = 0; j <= 2; ++j) if (board[i + j] == 0 && board[i + j + 1] == player && board[i + j + 2] == 0 && board[i + j + 3] == player && board[i + j + 4] == 0) {
			return true;
		}
	}
	for (size_t i = 0; i < 7; ++i) {
		for (size_t j = 0; j <= 14; j += 7) if (board[i + j] == 0 && board[i + j + 7] == player && board[i + j + 14] == player && board[i + j + 21] == player) {
			return true;
		}
	}
	//diagonals
	for (size_t i = 10; i <= 17; i += 7) {
		for (size_t j = 0; j <= 3; ++j) {
			if (board[i + j] == player && board[i + j + 6] == player && board[i + j + 12] == player && board[i + j + 18] == 0) return true;
			if (board[i + j] == player && board[i + j + 6] == player && board[i + j + 12] == 0 && board[i + j + 18] == player) return true;
			if (board[i + j] == player && board[i + j + 6] == 0 && board[i + j + 12] == player && board[i + j + 18] == player) return true;
			if (board[i + j] == 0 && board[i + j + 6] == player && board[i + j + 12] == player && board[i + j + 18] == player) return true;

			if (board[i - j] == player && board[i - j + 8] == player && board[i - j + 16] == player && board[i - j + 24] == 0) return true;
			if (board[i - j] == player && board[i - j + 8] == player && board[i - j + 16] == 0 && board[i - j + 24] == player) return true;
			if (board[i - j] == player && board[i - j + 8] == 0 && board[i - j + 16] == player && board[i - j + 24] == player) return true;
			if (board[i - j] == 0 && board[i - j + 8] == player && board[i - j + 16] == player && board[i - j + 24] == player) return true;
		}

	}
	return false;
}


inline bool full() {
	for (int i = 0; i < 7; ++i) if (board[i] == 0) return false;
	return true;
}

inline bool fullcolumn(size_t col) {
	if (col < 1 or col>7) {
		return true;
	}
	else {
		--col; //o indice col vai de 1-7, e temos que converter isso pra 0-6
		if (board[col] == 0) return false;
		return true;
	}
}
inline bool fullcolumn(const std::vector<unsigned>& board, size_t col) {
	if (col < 1 or col>7) {
		return true;
	}
	else {
		--col; //o indice col vai de 1-7, e temos que converter isso pra 0-6
		if (board[col] == 0) return false;
		return true;
	}
}

inline bool placi(size_t place, short player) {
	if (place < 1 or place>7) {
		cout << "Erro: selecione uma coluna adequada" << endl;
		return false;
	}
	else {
		--place;
		size_t i = 0;
		while (i < 42 && board[place + i] == 0) i += 7;
		if (i) {
			board[place + i - 7] = player;
			return true;
		}
		else {
			cout << "Erro: a coluna ja esta cheia!" << endl;
			return false;
		}
	}
}
inline std::vector<unsigned> placi(std::vector<unsigned>& board, size_t place, short player) {
	--place;
	size_t i = 0;
	while (i < 42 && board[place + i] == 0) i += 7;
	if (i) board[place + i - 7] = player;
	return board;
}

//remover a peça mais elevada da coluna place, é importante para garantir que estamos testando estados válidos no algoritmo
inline bool remove(size_t place) {
	if (place < 1 or place>7) {
		cout << "Erro: selecione uma coluna adequada" << endl;
		return false;
	}
	else {
		--place;
		size_t i = 0;
		while (board[place + i] == 0 && i < 42) i += 7;
		if (i < 42) {
			board[place + i] = 0;
			return true;
		}
		else {
			cout << "Erro: Nao ha nada na coluna a ser retirado!" << endl;
			return false;
		}
	}
}

//retorna a "pontuação" da melhor jogada encontrada, e "pos" retorna a posição a ser jogada pela CPU, depth impede que o algoritmo
//gaste 10000000 de anos pesquisando toda a arvore do jogo, onde depois de ultrapassar a profundeza ele faz um chute torto
// (também conhecido como a função heuristica close to win) para determinar 
double best_play(unsigned& pos, short player = 2, unsigned depth = 0) {
	short opponent = (player == 1) ? 2 : 1;
	double victory = (player == 1) ? 400 : -400;
	vector<unsigned> moves;
	if (win(opponent)) return -victory;
	if (win(player)) return victory;
	if (full()) return 0;
	if (depth > 4) {
		if (closetowin(opponent)) return -victory / 2;
		if (closetowin(player)) return victory / 2;
		return 0;
	}
	unsigned dummy; //dummy variable for recursive calls
	double best = (player == 1) ? DBL_MIN : DBL_MAX;; //the best score
	double current; //current score
	for (unsigned i = 1; i <= 7; ++i) {
		if (!fullcolumn(i)) {
			placi(i, opponent);
			if (win(opponent)) {
				pos = i;
				remove(i);
				placi(i, player);
				auto temp = best_play(dummy, opponent, depth + 1);
				remove(i);
				return temp;
			}
			remove(i);
			placi(i, player);
			if (win(player)) {
				pos = i;
				remove(i);
				return victory;
			}
			current = best_play(dummy, opponent, depth + 1);
			if ((player == 1 && current > best) || (player == 2 && current < best)) {
				moves.clear();
				best = current;
				moves.push_back(i);
			}
			else if (current == best) moves.push_back(i);
			remove(i);
		}
	}
	//eu decidi tornar a jogada meio que aleatoria para ficar mais divertido
	if (depth == 0) {
		srand(time(NULL));
		auto s = moves.size();
		if (s > 0) {
			auto m = rand() % s;
			pos = moves[m];
		}
	}
	return best;
}

inline void print(void* HANDLE) {
	for (auto i = 0; i < 42; ++i) {
		if (i != 0 && i % 7 == 0) cout << endl;
		switch (board[i]) {
		case 1:
			SetConsoleTextAttribute(HANDLE, 4);
			cout << "H ";
			break;
		case 2:
			SetConsoleTextAttribute(HANDLE, 1);
			cout << "P ";
			break;
		default:
		case 0:
			SetConsoleTextAttribute(HANDLE, 15);
			cout << "O ";
			break;
		}
		SetConsoleTextAttribute(HANDLE, 15);
	}
	cout << endl;
	for (auto i = 1; i < 8; ++i) cout << i << ' ';
	cout << endl;
	cout << endl;
}
inline void print(std::vector<unsigned> board, void* HANDLE) {
	cout << "This... is a test, wouldn't you agree, jean pierre polnareff?" << endl;
	for (auto i = 0; i < 42; ++i) {
		if (i != 0 && i % 7 == 0) cout << endl;
		switch (board[i]) {
		case 1:
			SetConsoleTextAttribute(HANDLE, 4);
			cout << "H ";
			break;
		case 2:
			SetConsoleTextAttribute(HANDLE, 1);
			cout << "P ";
			break;
		default:
		case 0:
			SetConsoleTextAttribute(HANDLE, 15);
			cout << "O ";
			break;
		}
		SetConsoleTextAttribute(HANDLE, 15);
	}
	cout << endl;
	for (auto i = 1; i < 8; ++i) cout << i << ' ';
	cout << endl;
	cout << endl;
}

#include<map>
#include<cstdio>
struct state {
	std::vector<unsigned> board;
	state(bool copy=false): board(42,0) {
		if (copy) {
			for (int i = 0; i < 42; ++i) {
				board[i] = ::board[i];
			}
		}
	}
	void set_board() {
		for (int i = 0; i < 42; ++i) {
			::board[i] = board[i];
		}
	}
	state(const state& st) = default;
	bool operator<(const state& r) const {
		return board < r.board;
	}
};
struct state_action {
	state stat;
	int action;
};
namespace std {
	template<> struct std::less<state_action> {
		bool operator()(const state_action& l, const state_action& r) const {
			auto p1 = std::make_pair(l.stat, l.action);
			auto p2 = std::make_pair(r.stat, r.action);
			return p1 < p2;
		}
	};
}
struct q_agent {
	double discount=0.95,learning_rate=0.9;
	int epsilon=11;
	int turn = 0;
	int player=1;
	std::map<state_action, double> Q_table;

	q_agent(int i):player(i) {}
	void store_Q_table() const {
		FILE* fp = fopen("Table", "w");
		fwrite((&Q_table), sizeof(std::map<state_action, double>), 1, fp);
		fclose(fp);
	}
	void load_Q_table() {
		FILE* fp = fopen("Table", "r");
		fread((&Q_table), sizeof(std::map<state_action, double>), 1, fp);
		fclose(fp);
	}
	double maxQ(const state& st, int& action) {
		state_action sa{ st,0 };
		double Q_max = -DBL_MAX;
		for (int i = 1; i <= 7; ++i) {
			if (fullcolumn(st.board, i)) continue;
			sa.action = i;
			if (Q_table[sa] > Q_max) {
				action = i;
				Q_max = Q_table[sa];
			}
		}
		return Q_max;
	}
	state new_state(const state& st, int peg) {
		state copy = st;
		placi(copy.board, peg, player);
		return copy;
	}
	double reward(const state& st) {
		if (win(st.board, 2) && player==1) return -999;
		if (win(st.board, 1) && player==1) return 999;
		if (win(st.board, 2) && player == 2) return 999;
		if (win(st.board, 1) && player == 2) return -999;
		if (closetowin(st.board, 2) && player==1) return -100;
		if (closetowin(st.board, 1) && player==1) return 100;
		if (closetowin(st.board, 2) && player==2) return 100;
		if (closetowin(st.board, 1) && player==2) return -100;
		return 0;
	}
	double newQ(const state_action& sa) {
		int dummy = sa.action;
		return reward(new_state(sa.stat,sa.action)) + discount * (maxQ(new_state(sa.stat,sa.action), dummy));
	}
	void play(state& game_state) {
		auto r = rand() % 10;
		int peg = 0;
		if (r > epsilon) {
			maxQ(game_state, peg);
		}
		else {
			peg = rand() % 7 + 1;
			while (fullcolumn(game_state.board, peg)) peg = rand() % 7 + 1;
		}
		state_action sa{ game_state,peg };
		Q_table[sa] = (1 - learning_rate) * Q_table[sa] + learning_rate * newQ(sa);
		game_state = new_state(game_state,peg);
		++turn;
		if (turn % 6000 == 0 && epsilon>3) --epsilon;
		cout << "My play: " << peg << endl;
		/*
		if(Random Number>epsilon) {
			select action with best Q-value for current game-state
		else select action at random
		compute the new Q-value from doing the chosen action at the current state
		do action, change game state
		//after many times exploring, reduce epsilon to exploit
		++turn
		if(turn%1000==0) --epsilon;
		*/
	}
	/*
	Formulas:
	Define Value or potential of state: V(S0)=max{At,t=0 until inf}(Sum[t=0 until inf](discount^t*R(St,At)))
	V(S0)=max{A0}(R(S0,A0)+discount*max{At,t=1 until inf}(Sum[t=1 until inf](discount^(t-1)*R(St,At)))
	V(S0)=max{A0}(R(S0,A0)+discount*V(S1))
	V(S)=max{A}(R(S,A)+discount*V(T(S,A))) (new state S'=T(S,A))
	define Quality of Action: Q(S,A)=R(S,A)+discount*V(S')
	Therefore V(S)=max{A}(Q(S,A))

	Q(S,A)=R(S,A)+discount*Max{A'}(Q(S',A'))
	define Temporal Differrence: TD(S,A)=New Q(S,A)- Old Q(S,A)
	therefore:
	TD(S,A)= R(S,A)+discount*Max{A'}(Q(S',A'))- Q(S,A)
	Update the Q-value:
	Q(S,A)=(1-learning_rate)*Q(S,A)+learning_rate*(TD(S,A))
	*/
};


int main() {
	auto h = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned menu_input, input;
	unsigned cpu;
	short player = 1;
	while (true) {
		cout << "Selecione uma opcao:" << endl;
		cout << "0-Ajuda" << endl;
		cout << "1-Modo PvP" << endl;
		cout << "2-Modo vs CPU" << endl;
		cout << "3-Olhe 2 CPU tentando se matar" << endl;
		cout << "4-Sair" << endl;
		cout << "5-Treinar meu garoto" << endl;
		cin >> menu_input;
		switch (menu_input) {
		case 0:
			cout << "Cada jogador tem seu turno para colocar uma de suas peças na fileira que desejar" << endl;
			cout << "Ganha quem conseguir criar um arranjo de 4 de suas pecas consecutivas, seja na diagonal, vertical ou horizontal" << endl;
			cout << "Digite um número entre 1 e 7 (as colunas sao enumeradas para facilitar)" << endl;
			cout << "Depois aperte Enter para confirmar sua jogada" << endl;
			cout << "Caso esteja jogando contra a CPU, pode parecer que o terminal travou, tenha um pouco de paciencia" << endl << "e espere alguns segundos" << endl;
			cout << "Se ainda assim continuar travado, apertar algum botao dentro do terminal ajuda algumas vezes" << endl;
			cout << endl << endl;
			break;
		case 1:
			reset();
			player = 1;
			while (!win((player % 2) + 1) and !full()) {
				print(h);
				cout << "Jogador " << player << ": ";
				cin >> input;
				if (!placi(input, player)) continue;
				player = (player == 1) ? 2 : 1;
			}
			print(h);
			if (win(player % 2 + 1)) cout << "Vitoria do Jogador " << player % 2 + 1 << "!" << endl;
			else cout << "Empatou :P" << endl;
			break;
		case 2:
			reset();
			player = 2;
			while (!win(player) and !full()) {
				player = (player % 2) + 1;
			error:
				print(h);
				if (player == 1) {
					cout << "Jogador: ";
					cin >> input;
					if (!placi(input, player)) goto error;
				}
				else {
					best_play(cpu);
					placi(cpu, 2);
					cout << "Computador: " << cpu << endl;
				}
			}
			print(h);
			if (win(player)) {
				std::string message = (player == 1) ? "o Jogador!" : "a CPU!";
				cout << "Vitoria d" + message;
				cout << endl;
			}
			else cout << "Empatou :P" << endl;
			break;
		case 3:
			reset();
			player = 1;
			while (!win(1) and !win(2) and !full()) {
				print(h);
				best_play(cpu, player);
				placi(cpu, player);
				cout << "CPU " << player << ": " << cpu << endl;
				player = (player % 2) + 1;
			}
			print(h);
			if (win((player % 2) + 1)) cout << "CPU " << (player % 2) + 1 << " Ganhou!" << endl;
			else cout << "Empatou :P" << endl;
			break;
		case 4:
			exit(0);
			break;
		case 5:
			q_agent q(1);
		restart:
			int match = 200000;
			while (match>0) {
				reset();
				player = 1;
				while (!win(1) and !win(2) and !full()) {
					srand(clock());
					state game(true);
					print(h);
					if (player == 1) {
						cout << "Test Bot 1: ";
						q.play(game);
						game.set_board();
					}
					else {
						best_play(cpu);
						placi(cpu, 2);
						cout << "Computador: " << cpu << endl;
					}
					player = (player == 1) ? 2 : 1;
				}
				print(h);
				--match;
			}
			char c;
			cout << "Restart?[y/n]:";
			cin >> c;
			if (c == 'y') goto restart;
		}
	}
	system("pause");
	return 0;
}