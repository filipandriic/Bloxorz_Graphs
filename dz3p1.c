#include<stdio.h>
#include<string.h>
#include<Windows.h>
#define MAX 100

int a, b = 0;
int n = 0;
int cvor = 1;
int Matrix[MAX][MAX];
int Help[MAX][MAX];
int positions[2];
int Block = -1, Block1 = -1;

typedef struct Node {
	int value;
	struct Node* right;
} node;

node *head = NULL;
node *tail = NULL;

void Insert(node *cvor) {

	if (head == NULL) {
		head = cvor;
		tail = cvor;
	}
	else {
		tail->right = cvor;
		tail = cvor;
	}
}

node* Delete() {
	node* temp = head;

	if (temp == NULL) {
		printf("Red je prazan.\n");
	}

	else {
		if (head == tail) {
			head = NULL;
			tail = NULL;
		}
		else
			head = head->right;
	}

	return temp;
}

void MakeHelp() {
	int i, j;
	char tek[MAX];
	FILE *ulaz = NULL;

	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
			Help[i][j] = 0;
		
	ulaz = fopen("Tabla.txt", "r");
	i = 0;
	while (fgets(tek, 100, ulaz)) {
		a = strlen(tek);
		for (j = 0; j < a; j++)
			if (tek[j] != '-' && tek[j] != '\n') {
				Help[i][j] = cvor;
				
				if (tek[j] == 'S')
					positions[0] = cvor;
				
				if (tek[j] == 'T')
					positions[1] = cvor;
				cvor++;
				n++;
			}
		b++;
		i++;
	}

	fclose(ulaz);
}

void MakeGraph() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) 
			Matrix[i][j] = 0;
		

	for (int i = 0; i < b; i++)
		for (int j = 0; j < a; j++) {
			if (Help[i][j] > 0) {
				// levi
				if (j > 0)
					if (Help[i][j - 1] > 0)
						Matrix[Help[i][j] - 1][Help[i][j - 1] - 1] = 1;
				//desni
				if (Help[i][j + 1] > 0)
					Matrix[Help[i][j] - 1][Help[i][j + 1] - 1] = 1;
				//donji
				if (Help[i + 1][j] > 0)
					Matrix[Help[i][j] - 1][Help[i + 1][j] - 1] = 1;
				//gornji
				if (i > 0)
					if (Help[i - 1][j] > 0)
						Matrix[Help[i][j] - 1][Help[i - 1][j] - 1] = 1;
			}
		}
}

void AddElement() {
	int v, k;
	int temp = 0;
	
	printf("Na koju poziciju zelite da unesete plocu: \n");
	printf("              Vrsta: ");
	scanf("%d", &v);
	printf("              Kolona: ");
	scanf("%d", &k);

	if (((v - 1) <= b) && ((k - 1) <= a)) {
		if (Help[v - 1][k - 1] == 0) {
			for (int i = 0; i < v; i++)
				for (int j = 0; j < a; j++) {
					if (Help[i][j] != 0)
						temp = Help[i][j];
				}

			Help[v - 1][k - 1] = temp + 1;
			for (int i = v; i < b; i++)
				for (int j = 0; j < a; j++) {
					if (Help[i][j] != 0)
						Help[i][j]++;
				}

			if (temp < positions[0])
				positions[0]++;

			if (temp < positions[1])
				positions[1]++;

			if (temp < positions[2])
				positions[2]++;

			if (temp < positions[3])
				positions[3]++;

			cvor++;
			n++;
			MakeGraph();
			printf("Ploca je dodata.\n");
		}
		else
			printf("Prethodno je postojala ploca.\n");
	}
	else
		printf("Prekoracili ste ivicu terena.\n");
}

void EreaseElement() {
	int v, k;

	printf("Sa koje pozicije zelite da izbrisete plocu: \n");
	printf("              Vrsta: ");
	scanf("%d", &v);
	printf("              Kolona: ");
	scanf("%d", &k);

	if (((v - 1) <= b) && ((k - 1) <= a)) {
		if (Help[v - 1][k - 1] != 0) {
			for (int i = 0; i < b; i++)
				for (int j = 0; j < a; j++)
					if ((Help[v - 1][k - 1] < Help[i][j]) && (Help[i][j] != 0))
						Help[i][j] -= 1;

			if (Help[v - 1][k - 1] < positions[0])
				positions[0]--;

			if (Help[v - 1][k - 1] < positions[1])
				positions[1]--;

			if (Help[v - 1][k - 1] < positions[2])
				positions[2]--;

			if (Help[v - 1][k - 1] < positions[3])
				positions[3]--;

			Help[v - 1][k - 1] = 0;
			n--;
			cvor--;
			MakeGraph();
			printf("Ploca je izbrisana.\n");
		}
		else
			printf("Prethodno nije postojala ploca.\n");
	}
	else
		printf("Prekoracili ste ivicu terena.\n");
}

void PrintMatrix() {
	printf("Matrica susednosti je:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j == 0)
				printf("| [%d] ", Matrix[i][j]);
			else
				if (j == n - 1)
					printf("[%d] |", Matrix[i][j]);
				else
					printf("[%d] ", Matrix[i][j]);
		}
		printf("\n");
	}
}

void FilePrint() {
	FILE *izlaz = NULL;
	char naziv[30];

	printf("Unesite ime izlazne datoteke? ");
	scanf("%s", naziv);

	izlaz = fopen(naziv, "w");
	for (int i = 0; i < b; i++) {
		for (int j = 0; j < a; j++) {
			if (Help[i][j] != 0)
				if (Help[i][j] == positions[0])
					fputc('S', izlaz);
				else
					if (Help[i][j] == positions[1])
						fputc('T', izlaz);
					else
						fputc('o', izlaz);
			else
				fputc('-', izlaz);
		}
		fputc('\n', izlaz);
	}

	fclose(izlaz);
}

void TablePrint() {
	for (int i = 0; i < b; i++) {
		printf("     ");
		for (int j = 0; j < a; j++) {
			if (Help[i][j] != 0)
				if (Help[i][j] == positions[0])
					printf("S");
				else
					if (Help[i][j] == positions[1])
						printf("T");
					else
						printf("o");
			else
				printf("-");
		}
		printf("\n");
	}
}

void TablePrintGame(HANDLE h) {
	for (int i = 0; i < b; i++) {
		printf("     ");
		for (int j = 0; j < a; j++) {
			if (Help[i][j] != 0)
				if (Help[i][j] == positions[0]) {
					if (Help[i][j] == Block || Help[i][j] == Block1)
						SetConsoleTextAttribute(h, 10);
					printf("S");
					SetConsoleTextAttribute(h, 15);
				}
				else
					if (Help[i][j] == positions[1]) {
						if (Help[i][j] == Block || Help[i][j] == Block1)
							SetConsoleTextAttribute(h, 10);
						printf("T");
						SetConsoleTextAttribute(h, 15);
					}
					else {
						if (Help[i][j] == Block || Help[i][j] == Block1)
							SetConsoleTextAttribute(h, 10);
						printf("o");
						SetConsoleTextAttribute(h, 15);
					}
			else
				printf("-");
		}
		printf("\n");
	}
}

void PlayGame(HANDLE h) {
	//pocetna pozicija
	//blok je na S
	char move;
	int choice = 0;
	int v, k;

	Block = positions[0];
	TablePrintGame(h);

	//nastavak igre
	while (1) {
		getchar();
		printf("Vas potez? ");
		scanf("%c", &move);

		if (move == 'w')
			choice = 1;

		if (move == 's')
			choice = 2;

		if (move == 'a')
			choice = 3;

		if (move == 'd')
			choice = 4;

		switch (choice) {
		case 1:
			//potez na gore
			if (Block1 == -1) {

				for (int i = 0; i < b; i++)
					for (int j = 0; j < a; j++)
						if (Help[i][j] == Block) {
							v = i;
							k = j;
						}


				Block1 = Help[v - 1][k];
				Block = Help[v - 2][k];

				if (Block == positions[1] && Block1 == -1) {
					TablePrintGame(h);
					SetConsoleTextAttribute(h, 10);
					printf("Pobedili ste.\n");
					exit(0);
				}

				if (Block == 0 || Block1 == 0) {
					SetConsoleTextAttribute(h, 10);
					printf("Izgubili ste.\n");
					exit(0);
				}
				else		
					TablePrintGame(h);
			}
			else {
				for (int i = 0; i < b; i++)
					for (int j = 0; j < a; j++)
						if (Help[i][j] == Block) {
							v = i;
							k = j;
						}

				if (Block1 == Help[v][k + 1]) {
					Block = Help[v - 1][k];
					Block1 = Help[v - 1][k + 1];
				}
				else {
					Block = Help[v - 1][k];
					Block1 = -1;
				}

				if (Block == positions[1] && Block1 == -1) {
					TablePrintGame(h);
					SetConsoleTextAttribute(h, 10);
					printf("Pobedili ste.\n");
					exit(0);
				}

				if (Block == 0 || Block1 == 0) {
					SetConsoleTextAttribute(h, 10);
					printf("Izgubili ste.\n");
					exit(0);
				}
				else
					TablePrintGame(h);
			}

			break;

		case 2:
			//potez na dole
			if (Block1 == -1) {

				for (int i = 0; i < b; i++)
					for (int j = 0; j < a; j++)
						if (Help[i][j] == Block) {
							v = i;
							k = j;
						}


				Block = Help[v + 1][k];
				Block1 = Help[v + 2][k];

				if (Block == positions[1] && Block1 == -1) {
					TablePrintGame(h);
					SetConsoleTextAttribute(h, 10);
					printf("Pobedili ste.\n");
					exit(0);
				}

				if (Block == 0 || Block1 == 0) {
					SetConsoleTextAttribute(h, 10);
					printf("Izgubili ste.\n");
					exit(0);
				}
				else
					TablePrintGame(h);
			}
			else {
				for (int i = 0; i < b; i++)
					for (int j = 0; j < a; j++)
						if (Help[i][j] == Block) {
							v = i;
							k = j;
						}

				if (Block1 == Help[v][k + 1]) {
					Block = Help[v + 1][k];
					Block1 = Help[v + 1][k + 1];
				}
				else {
					Block = Help[v + 2][k];
					Block1 = -1;
				}

				if (Block == positions[1] && Block1 == -1) {
					TablePrintGame(h);
					SetConsoleTextAttribute(h, 10);
					printf("Pobedili ste.\n");
					exit(0);
				}

				if (Block == 0 || Block1 == 0) {
					SetConsoleTextAttribute(h, 10);
					printf("Izgubili ste.\n");
					exit(0);
				}
				else
					TablePrintGame(h);
			}

			break;

			case 3:
				//potez u levo
				if (Block1 == -1) {

					for (int i = 0; i < b; i++)
						for (int j = 0; j < a; j++)
							if (Help[i][j] == Block) {
								v = i;
								k = j;
							}

					Block1 = Help[v][k - 1];
					Block = Help[v][k - 2];

					if (Block == positions[1] && Block1 == -1) {
						TablePrintGame(h);
						SetConsoleTextAttribute(h, 10);
						printf("Pobedili ste.\n");
						exit(0);
					}

					if (Block == 0 || Block1 == 0) {
						SetConsoleTextAttribute(h, 10);
						printf("Izgubili ste.\n");
						exit(0);
					}
					else
						TablePrintGame(h);
				}
				else {
					for (int i = 0; i < b; i++)
						for (int j = 0; j < a; j++)
							if (Help[i][j] == Block) {
								v = i;
								k = j;
							}

					if (Block1 == Help[v + 1][k]) {
						Block = Help[v][k - 1];
						Block1 = Help[v + 1][k - 1];
					}
					else {
						Block = Help[v][k - 1];
						Block1 = -1;
					}

					if (Block == positions[1] && Block1 == -1) {
						TablePrintGame(h);
						SetConsoleTextAttribute(h, 10);
						printf("Pobedili ste.\n");
						exit(0);
					}

					if (Block == 0 || Block1 == 0) {
						SetConsoleTextAttribute(h, 10);
						printf("Izgubili ste.\n");
						exit(0);
					}
					else
						TablePrintGame(h);
				}
				break;

			case 4:
				//potez u desno
				if (Block1 == -1) {

					for (int i = 0; i < b; i++)
						for (int j = 0; j < a; j++)
							if (Help[i][j] == Block) {
								v = i;
								k = j;
							}

					Block = Help[v][k + 1];
					Block1 = Help[v][k + 2];

					if (Block == positions[1] && Block1 == -1) {
						TablePrintGame(h);
						SetConsoleTextAttribute(h, 10);
						printf("Pobedili ste.\n");
						exit(0);
					}

					if (Block == 0 || Block1 == 0) {
						SetConsoleTextAttribute(h, 10);
						printf("Izgubili ste.\n");
						exit(0);
					}
					else
						TablePrintGame(h);
				}
				else {
					for (int i = 0; i < b; i++)
						for (int j = 0; j < a; j++)
							if (Help[i][j] == Block) {
								v = i;
								k = j;
							}

					if (Block1 == Help[v + 1][k]) {
						Block = Help[v][k + 1];
						Block1 = Help[v + 1][k + 1];
					}
					else {
						Block = Help[v][k + 2];
						Block1 = -1;
					}

					if (Block == positions[1] && Block1 == -1) {
						TablePrintGame(h);
						SetConsoleTextAttribute(h, 10);
						printf("Pobedili ste.\n");
						exit(0);
					}

					if (Block == 0 || Block1 == 0) {
						SetConsoleTextAttribute(h, 10);
						printf("Izgubili ste.\n");
						exit(0);
					}
					else
						TablePrintGame(h);
				}
				break;
		}
	}
}

/*void FindIndex(int node, int* v, int* k) {
	for (int i = 0; i < b; i++)
		for (int j = 0; j < a; j++) {
			if (Help[i][j] == node) {
				*v = 
			}
		}
}*/

void PathFinder() {
	//BFS search
	//3 stanja, kodiraj
	int v, cond;
	int conditions[3];
	int visit[MAX];
	conditions[0] = 1; //kada je uspravan
	conditions[1] = 2; //kada je polozen vertikalno
	conditions[2] = 3; //kada je polozen horizontalno

	//postavi visit na false
	for (int i = 0; i < n; i++)
		visit[i] = 0;

	cond = 1;
	v = positions[0] - 1;
	Block = positions[0];
	node* cvor = malloc(sizeof(node));
	cvor->value = positions[0];
	cvor->right = NULL;
	Insert(cvor);

	while (head != NULL) {
		//idi gore
		if (cond == 1) {

		}
		else
			if (cond == 2) {

			}
			else {

			}

		//idi dole
		//idi levo
		//idi desno
	}
}

int main() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int choice;
	
	while (1) {
	printf("      MENU\n"
		"1. Napravite graf.\n"
		"2. Prikazite graf preko matrice.\n"
		"3. Prikazite tablu.\n"
		"4. Dodajte plocu.\n"
		"5. Izbrisite plocu.\n"
		"6. Odstampajte tablu u izlaznu datoteku.\n"
		"7. Pocni igru.\n"
		"0. Napusti program.\n");
	scanf("%d", &choice);
	
		switch (choice) {
		case 1:
			MakeHelp();
			MakeGraph();
			printf("Mozete da pocnete sa programom.\n");
			break;

		case 2:
			PrintMatrix();
			break;

		case 3:
			TablePrint();
			break;

		case 4:
			AddElement();
			break;
			
		case 5:
			EreaseElement();
			break;

		case 6:
			FilePrint();
			break;

		case 7:
			PlayGame(h);
			break;

		case 8:
			PathFinder();
			break;

		case 0:
			SetConsoleTextAttribute(h, 10);
			printf("Dovidjenja!\n");
			exit(0);
			break;
		}
	}
}