#include<iostream>
#include<string>
#include<vector>
#include <cmath>

using namespace std;

struct Board
{
        int S; // rozmiar planszy
        int K; // liczba pionów gracza która wyzwala zbieranie pionów z rzędu
        int GW; // liczba pionów należących do gracza białego
        int GB; // liczba pionów należących do gracza czarnego
        int WR; // rezerwa białego gracza
        int BR; // rezerwa gracza czarnego 
        char Active_Player; // który gracz zaczyna
        int AWP = 0; // aktywne białe pionki
        int ABP = 0; // aktywne czarne pionki
        char** board;
};

//zwraca 0 gdy nie wykryto w rzędzie K tych samych pionów pod rząd
//zwraca 1 gdy jest >= k czarnych pod rząd
//zwraca 2 gdy jest >= k bialych pod rząd
int CHECK_ROW_FOR_K(Board s_board, int Dest[2], int Start[2])
{                                                                                                                
                int col = Start[0] - 98;
                int row;

                int transfer = 0;

                int vector_y = Start[1] - Dest[1];
                int vector_x = Dest[0] - Start[0];

                if (Start[0] - 98 < s_board.S) // dla indeksów kolumn przed  i na przekątnej
                {
                        row = s_board.S * 2 - Start[1];
                }
                else
                {
                        transfer = Start[0] - 98 - (s_board.S - 1);             // przenieniesienie równe "odległości" kolumny od kolumny przekątnej
                        row = s_board.S * 2 - 2 - transfer + (2 - Start[1]);    // row jest równe indekowi ostatniego elementu tablicy od którego odejmujemy przeniesienie i odległość od 2 
                        int x = Dest[0] - Start[0];
                        vector_y = Start[1] - x - Dest[1];
                        //vector_y = Remove_From_Imput[1] - Remove_To_Imput[1] + (Remove_From_Imput[0] - 98 - (s_board.S - 1));
                }

                int counter = 0;
                char Last_Char = 'u'; // u - uniwersalny
                while (true)
                {
                        row += vector_y;
                        col += vector_x;

                        if (col < 0 || col > s_board.S * 2 - 2 || row < 0 || row > s_board.S * 2 - 2)   // czy x i y mieszczą się w mapie 
                        {
                                break;
                        }
                        if (s_board.board[row][col] == ' ')
                        {
                                break;
                        }
                        if (s_board.board[row][col] == '_')
                        {
                                Last_Char = 'u';
                                counter = 0;
                        }
                        else if (s_board.board[row][col] == Last_Char || Last_Char == 'u')
                        {
                                counter++;
                                Last_Char = s_board.board[row][col];\
                                if (counter >= s_board.K)
                                {
                                        if (Last_Char == 'B') return 1;
                                        else return 2;
                                }
                        }
                        else
                        {
                                counter = 1;
                                Last_Char = s_board.board[row][col];
                        }
                }
        return 0;
}


// funkcja zamienia idnex kolumny z planszy na indeks kolumny z tablicy dla mode=0 
// i na odwrót dla mode=1
int CONVERT_INDEX_COL(int Cord[2], int mode)
{
        if (!mode)
        {
                return Cord[0] - 98;
        }
        else
        {
                return Cord[1] + 98;
        }

}


// funkcja zamienia indeks wiersza z planszy na indeks wiersza z tablicy dla mode = 0 
// i na odwrót dla mode = 1
int CONVERT_INDEX_ROW(int Cord[2], int mode, Board s_board)
{
        if (!mode)
        {
                if (Cord[0] - 98 > s_board.S - 1) // dla indeksow za przekątną
                {
                        int transfer = Cord[0] - 98 - (s_board.S - 1);
                        return s_board.S * 2 - Cord[1] - transfer;
                }
                else
                {
                        return s_board.S * 2 - Cord[1];
                }
        }
        else
        {
                if (Cord[0] - 98 > s_board.S - 1) // dla indeksow za przekątną
                {
                        int transfer = Cord[0] - 98 - (s_board.S - 1);
                        return s_board.S * 2 - Cord[0] - transfer;
                }
                else
                {
                        return s_board.S * 2 - Cord[0];
                }

        }
}

void COMMIT_MOVE(Board* s_board, int Start[2], int Dest[2])
{
        if (s_board->board[CONVERT_INDEX_ROW(Dest, 0, *s_board)][CONVERT_INDEX_COL(Dest, 0)] == '_')
        {
                s_board->board[CONVERT_INDEX_ROW(Dest, 0, *s_board)][CONVERT_INDEX_COL(Dest, 0)] = s_board->Active_Player;
                {
                        if (s_board->Active_Player == 'B')
                        {
                                s_board->BR--;
                                s_board->Active_Player = 'W';
                        }
                        else if (s_board->Active_Player == 'W')
                        {
                                s_board->WR--;
                                s_board->Active_Player = 'B';
                        }
                }
        }
        else
        {
                int col = Start[0] - 98;
                int row;

                int transfer = 0;

                int vector_y = Start[1] - Dest[1];
                int vector_x = Dest[0] - Start[0];

                if (Start[0] - 97 <= s_board->S) // dla indeksów kolumn przed przekątną
                {
                        row = s_board->S * 2 - Start[1];
                }
                else
                {
                        transfer = Start[0] - 98 - (s_board->S - 1);            // przenieniesienie równe "odległości" kolumny od kolumny przekątnej
                        row = s_board->S * 2 - 2 - transfer + (2 - Start[1]);   // row jest równe indekowi ostatniego elementu tablicy od którego odejmujemy przeniesienie i odległość od 2 
                        //vector_y = Start[1] + 1 - Dest[1];
                        int x = Dest[0] - Start[0];
                        vector_y = Start[1] - x - Dest[1];
                }

                char Pawn = s_board->Active_Player;
                char Pawn_temp;
                while (true)
                {
                        row += vector_y;
                        col += vector_x;
                        if (s_board->board[row][col] == 'B' || s_board->board[row][col] == 'W')
                        {
                                Pawn_temp = s_board->board[row][col];
                                s_board->board[row][col] = Pawn;
                                Pawn = Pawn_temp;
                        }
                        else
                        {
                                s_board->board[row][col] = Pawn;
                                if (s_board->Active_Player == 'W')
                                {
                                        s_board->WR--;
                                        s_board->Active_Player = 'B';
                                }
                                else
                                {
                                        s_board->BR--;
                                        s_board->Active_Player = 'W';
                                }
                                break;
                        }
                }
        }
}


bool IS_SPACE_IN_ROW(Board s_board, int Start[2], int Dest[2])
{
        bool _free = false;
        if (s_board.board[CONVERT_INDEX_ROW(Dest, 0, s_board)][CONVERT_INDEX_COL(Dest, 0)] == '_')  // jezeli wybrane pole to '_'
        {
                return true;
        }
        else  // w przeciwnym razie sprawdza czy wybrany rząd jest pełny
        {
                int col = Start[0] - 98;
                int row;

                int transfer = 0;

                int vector_y = Start[1] - Dest[1];
                int vector_x = Dest[0] - Start[0];

                if (Start[0] - 98 < s_board.S) // dla indeksów kolumn przed przekątną
                {
                        row = s_board.S * 2 - Start[1];
                }
                else
                {
                        transfer = Start[0] - 98 - (s_board.S - 1);             // przenieniesienie równe "odległości" kolumny od kolumny przekątnej
                        row = s_board.S * 2 - 2 - transfer + (2 - Start[1]);    // row jest równe indekowi ostatniego elementu tablicy od którego odejmujemy przeniesienie i odległość od 2 
                        int x = Dest[0] - Start[0];
                        vector_y = Start[1] - x - Dest[1];
                        //vector_y = Start[1] + 1 - Dest[1];
                }

                while (1)
                {
                        row += vector_y;
                        col += vector_x;

                        if (col < 0 || col > s_board.S*2 - 2 || row < 0 || row > s_board.S*2 - 2)       // czy x i y mieszczą się w mapie 
                        {
                                break;
                        }
                        if (s_board.board[row][col] == '_')
                        {
                                _free = true;
                                break;
                        }
                        else if (s_board.board[row][col] == ' ')
                        {
                                break;
                        }
                }
        }

        return _free;
}


// mode 0 nie zwraca komunikatu
bool IS_MOVE_VALID(Board s_board, int Start[2], int Dest[2], int mode)
{
        // czy index literowy pola startowego miesci się na planszy

        if (Start[0] - 96 > s_board.S * 2 + 1 || Start[0] - 96 < 1)  
        {
                if(mode)
                        cout << endl << "BAD_MOVE_" << (char)Start[0]<< to_string(Start[1]) << "_IS_WRONG_INDEX";
                return false;
        }
        if (Start[1] < 1)       
        {
                if (mode)
                        cout << endl << "BAD_MOVE_" << (char)Start[0] << to_string(Start[1]) << "_IS_WRONG_INDEX";
                return false;
        }

        if (Dest[0] - 96 >= s_board.S * 2 + 1 || Dest[0] - 96 <= 1)
        {
                if (mode)
                        cout << endl << "BAD_MOVE_" << (char)Dest[0]<< to_string(Dest[1]) << "_IS_WRONG_INDEX";
                return false;
        }
        if (Dest[1] < 1)
        {
                if (mode)
                        cout << endl << "BAD_MOVE_" << (char)Dest[0] << to_string(Dest[1]) << "_IS_WRONG_INDEX";
                return false;
        }

        // czy istnieje index liczbowy dla podanego indexu literowego

        if (Start[0] - 96 < s_board.S  + 1)                     // dla indexu literowego przed przekątną
        {
                if (Start[1] > Start[0] - 96 + s_board.S)
                {
                        if (mode)
                                cout << endl << "BAD_MOVE_" << (char)Start[0] << to_string(Start[1]) << "_IS_WRONG_INDEX";
                        return false;
                }
        }
        else if (Start[0] - 96 > s_board.S + 1)  // dla indexu literowego po przekątnej
        {
                if (Start[1] > (s_board.S*2 + 1) - (Start[0] - 96 - (s_board.S + 1)))
                {
                        if (mode)
                                cout << endl << "BAD_MOVE_" << (char)Start[0] << to_string(Start[1]) << "_IS_WRONG_INDEX";
                        return false;
                }
        }
        else if (Start[1] > s_board.S*2 + 1) // dla indexu literowego na przekątnej
        {
                if (mode)
                        cout << endl << "BAD_MOVE_" << (char)Start[0] << to_string(Start[1]) << "_IS_WRONG_INDEX";
                return false;
        }

        /// to samo dla Dest

        if (Dest[0] - 96 < s_board.S + 1)                       // dla indexu literowego przed przekątną
        {
                if (Dest[1] >= Dest[0] - 96 + s_board.S || Dest[1] == 1)
                {
                        if (mode)
                                cout << endl << "BAD_MOVE_" << (char)Dest[0] << to_string(Dest[1]) << "_IS_WRONG_DESTINATION_FIELD";
                        return false;
                }
        }
        else if (Dest[0] - 96 > s_board.S + 1)  // dla indexu literowego po przekątnej
        {
                if (Dest[1] >= (s_board.S * 2 + 1) - (Dest[0] - 96 - (s_board.S + 1)) || Dest[1] == 1)
                {
                        if (mode)
                                cout << endl << "BAD_MOVE_" << (char)Dest[0] << to_string(Dest[1]) << "_IS_WRONG_DESTINATION_FIELD";
                        return false;
                }
        }
        else if (Dest[1] > s_board.S * 2 + 1 || Dest[1] == 1) // dla indexu literowego na przekątnej
        {
                if (mode)
                        cout << endl << "BAD_MOVE_" << (char)Dest[0] << to_string(Dest[1]) << "_IS_WRONG_DESTINATION_FIELD";
                return false;
        }
        
        if (Start[0] - 96 == 1) // dla Start[0] = 'a'
        {
                if (Dest[0] != 98)      // jezeli Dest[0] != 'b'
                {
                        if (mode)
                                cout << endl << "UNKNOWN_MOVE_DIRECTION";
                        return false;
                }
                else if (Dest[1] != Start[1] && Dest[1] != Start[1] + 1)
                {
                        if (mode)
                                cout << endl << "UNKNOWN_MOVE_DIRECTION";
                        return false;
                }
        }
        else if (Start[0] - 96 == s_board.S * 2 + 1)  // dla Start[0] = ostatni rząd
        {
                if (Dest[0] - 96 != s_board.S * 2)
                {
                        if (mode)
                                cout << endl << "UNKNOWN_MOVE_DIRECTION";
                        return false;
                }
                else if (Dest[1] != Start[1] && Dest[1] != Start[1] + 1)
                {
                        if (mode)
                                cout << endl << "UNKNOWN_MOVE_DIRECTION";
                        return false;
                }
        }
        else if (Start[0] - 96 < s_board.S + 1) // dla start[0] przed przekątną 
        {
                if (Start[1] == 1)
                {
                        if (Dest[0] == Start[0] || Dest[0] == Start[0] + 1)
                        {
                                if (Dest[1] != 2)
                                {
                                        if (mode)
                                                cout << endl << "UNKNOWN_MOVE_DIRECTION";
                                        return false;
                                }
                        }
                        else
                        {
                                if (mode)
                                        cout << endl << "UNKNOWN_MOVE_DIRECTION";
                                return false;
                        }
                }
                else if (Start[1] == s_board.S + Start[0] - 96)
                {
                        if (Dest[0] == Start[0] || Dest[0] == Start[0] + 1)
                        {
                                if (Dest[1] != Start[1] - 1 && Dest[1] != Start[1])
                                {
                                        if (mode)
                                                cout << endl << "UNKNOWN_MOVE_DIRECTION";
                                        return false;
                                }
                        }
                        else
                        {
                                if (mode)
                                        cout << endl << "UNKNOWN_MOVE_DIRECTION";
                                return false;
                        }
                }
                else
                {
                        if (mode)
                                cout << endl << "BAD_MOVE_" << (char)Start[0] << to_string(Start[1]) << "_IS_WRONG_STARTING_FIELD";
                        return false;
                }
        }
        else if (Start[0] - 96 == s_board.S + 1) // dla start[0] na przekątnej
        {
                if (Start[1] == 1)
                {
                        if (Dest[0] != Start[0] || Dest[1] != 2)
                        {
                                if (mode)
                                        cout << endl << "UNKNOWN_MOVE_DIRECTION";
                                return false;
                        }
                }
                else if (Start[1] == s_board.S * 2 + 1)
                {
                        if (Dest[0] != Start[0] || Dest[1] != Start[1]-1)
                        {
                                if (mode)
                                        cout << endl << "UNKNOWN_MOVE_DIRECTION";
                                return false;
                        }
                }
                else 
                {        
                        if (mode)
                                cout << endl << "UNKNOWN_MOVE_DIRECTION";                       
                        return false;
                }
        }
        else if (Start[0] - 96 > s_board.S + 1) // dla start[0] za przekątną
        {
                if (Start[1] == 1)
                {
                        if (Dest[0] == Start[0] || Dest[0] == Start[0] - 1)
                        {
                                if (Dest[1] != 2)
                                {
                                        if (mode)
                                                cout << endl << "UNKNOWN_MOVE_DIRECTION";                                       
                                        return false;
                                }
                        }
                        else
                        {
                                if (mode)
                                        cout << endl << "UNKNOWN_MOVE_DIRECTION";                               
                                return false;
                        }
                }
                else if (Start[1] == (s_board.S*2 + 1) -  (Start[0] - 97 - (s_board.S)))
                {
                        if (Dest[0] == Start[0] || Dest[0] == Start[0] - 1)
                        {
                                if (Dest[1] != Start[1] - 1 && Dest[1] != Start[1])
                                {
                                        if (mode)
                                                cout << endl << "UNKNOWN_MOVE_DIRECTION";                                       
                                        return false;
                                }
                        }
                        else
                        {
                                if (mode)
                                        cout << endl << "UNKNOWN_MOVE_DIRECTION";                               
                                return false;
                        }
                }
                else
                {
                        if (mode)
                                cout << endl << "UNKNOWN_MOVE_DIRECTION";                       
                        return false;
                }
        }
        return 1;
}


//      funkcja znajduje indeksy "od" i "do" pionków do usunięcia       
// dla mode = 1 funkcja znajduje indeksy tylko pionow w K rzędzie
void FIND_INDEX_TO_REMOVE(Board s_board, int Start[2], int Dest[2], int Remove_From[2], int Remove_To[2], int mode)
{
        int col = Start[0] - 98;
        int row;

        int transfer = 0;

        int vector_y = Start[1] - Dest[1];
        int vector_x = Dest[0] - Start[0];

        if (Start[0] - 98 < s_board.S) // dla indeksów kolumn przed  i na przekątnej
        {
                row = s_board.S * 2 - Start[1];
        }
        else
        {
                transfer = Start[0] - 98 - (s_board.S - 1);             // przenieniesienie równe "odległości" kolumny od kolumny przekątnej
                row = s_board.S * 2 - 2 - transfer + (2 - Start[1]);    // row jest równe indekowi ostatniego elementu tablicy od którego odejmujemy przeniesienie i odległość od 2 
                vector_y = Start[1] + 1 - Dest[1];
        }

        int counter = 0;
        char Last_Char = 'u'; // u - uniwersalny


        Remove_From[0] = row + vector_y;
        Remove_From[1] = col + vector_x;

        bool Found_K = false;

        while (true)
        {
                row += vector_y;
                col += vector_x;
                

                if (col < 0 || col > s_board.S * 2 - 2 || row < 0 || row > s_board.S * 2 - 2)   // czy x i y mieszczą się w mapie 
                {
                        break;
                }
                if (s_board.board[row][col] == ' ')
                {
                        break;
                }
                if (s_board.board[row][col] == '_')
                {
                        Last_Char = 'u';
                        counter = 0;
                        if (!Found_K)
                        {
                                Remove_From[0] = row + vector_y;
                                Remove_From[1] = col + vector_x;
                        }
                        else
                        {
                                Remove_To[0] = row - vector_y;
                                Remove_To[1] = col - vector_x;
                                break;
                        }
                }
                else if (s_board.board[row][col] == Last_Char || Last_Char == 'u')
                {
                        counter++;
                        Last_Char = s_board.board[row][col];
                        if (counter == s_board.K)
                        {
                                Found_K = true;
                                if (mode) // indeksy tylko pionów zbijających
                                {
                                        Remove_From[0] = row - (s_board.K - 1) * vector_y;
                                        Remove_From[1] = col - (s_board.K - 1) * vector_x;
                                        while (true)
                                        {
                                                row += vector_y;
                                                col += vector_x;
                                                if (col < 0 || col > s_board.S * 2 - 2 || row < 0 || row > s_board.S * 2 - 2)   // czy x i y mieszczą się w mapie 
                                                {
                                                        break;
                                                }
                                                if (s_board.board[row][col] == ' ' || s_board.board[row][col] == '_' || s_board.board[row][col] != Last_Char)
                                                {
                                                        break;
                                                }
                                        }
                                        Remove_To[0] = row - vector_y;
                                        Remove_To[1] = col - vector_x;
                                        return;
                                }
                        }
                        if (Found_K)
                        {
                                Remove_To[0] = row;
                                Remove_To[1] = col;
                        }
                }
                else
                {
                        counter = 1;
                        Last_Char = s_board.board[row][col];
                        if (Found_K)
                        {
                                Remove_To[0] = row;
                                Remove_To[1] = col;
                        }
                }
        }
}


//      funkcja usuwa pionki od indeksu a do indeksu b (indeksy tablicy, nie planszy)
//      Color określa który gracz miał K rząd
void REMOVE_PAWNS_BY_INDEX(Board* s_board, int Remove_From[2], int Remove_To[2], char Color)
{
        int vector_y = Remove_To[0] - Remove_From[0];
        if (vector_y < 0) vector_y = -1;
        else if (vector_y > 0) vector_y = 1;
        int vector_x = Remove_To[1] - Remove_From[1];
        if (vector_x < 0) vector_x = -1;
        else if (vector_x > 0) vector_x = 1;
        int row = Remove_From[0];
        int col = Remove_From[1];
        if (Color == 'b') Color = 'B';
        else if(Color == 'w') Color = 'W';
        do
        {
                if (s_board->board[row][col] == Color)
                {
                        s_board->board[row][col] = '_';
                        if (Color == 'B')
                        {
                                s_board->BR++;
                        }
                        else
                                s_board->WR++;
                }
                else if (s_board->board[row][col] != '_')
                {
                        s_board->board[row][col] = '_';
                }

                row += vector_y;
                col += vector_x;


        } while (row != Remove_To[0] + vector_y || col != Remove_To[1] + vector_x);

}


// funkcja szuka i usuwa wszystkie rzędy zawierające co najmniej k jednakowych pionów pod rząd 
void REMOVE_K_ROWS_FROM_BOARD(Board *s_board)
{
        //rzędy poziome
        for (int x = 0; x < s_board->S * 2 - 1; x++)
        {
                int Start[2];
                int Dest[2];
                if (x < s_board->S)
                {
                        Start[0] = 97; // 'a'
                        Start[1] = 1 + x;

                        Dest[0] = 98; //  'b'
                        Dest[1] = Start[1] + 1;
                }
                else
                {
                        Start[0] = 94 + x; // 'b,c,...'
                        Start[1] = 1;

                        Dest[0] = Start[0] + 1;
                        Dest[1] = 2;
                }
                char Color;
                int temp = CHECK_ROW_FOR_K(*s_board, Dest, Start);
                if (temp == 1) Color = 'B';
                else if (temp == 2) Color = 'W';
                
                if (temp)
                {
                        int Remove_From[2];
                        int Remove_To[2];
                        FIND_INDEX_TO_REMOVE(*s_board, Start, Dest, Remove_From, Remove_To, 0);
                        REMOVE_PAWNS_BY_INDEX(s_board, Remove_From, Remove_To, Color);
                }
        }

        //rzędy '///'
        for (int x = 0; x < s_board->S * 2 - 1; x++)
        {
                int Start[2];
                int Dest[2];

                Start[0] = 98 + x;
                Start[1] = 1;

                Dest[0] = 98 + x;
                Dest[1] = 2;

                char Color;
                int temp = CHECK_ROW_FOR_K(*s_board, Dest, Start);
                if (temp == 1) Color = 'B';
                else if (temp == 2) Color = 'W';

                if (temp)
                {
                        int Remove_From[2];
                        int Remove_To[2];
                        FIND_INDEX_TO_REMOVE(*s_board, Start, Dest, Remove_From, Remove_To, 0);
                        REMOVE_PAWNS_BY_INDEX(s_board, Remove_From, Remove_To, Color);
                }
        }

        //rzędy '\\\'
        for (int x = 0; x < s_board->S * 2 - 1; x++)
        {
                int Start[2];
                int Dest[2];
                if (x < s_board->S)
                {
                        Start[0] = 97; // 'a'
                        Start[1] = 2 + x;

                        Dest[0] = 98; //  'b'
                        Dest[1] = Start[1];
                }
                else
                {
                        Start[0] = 94 + x; // 'b,c,...'
                        Start[1] = 2 + x;

                        Dest[0] = Start[0] + 1;
                        Dest[1] = Start[1];
                }

                char Color;
                int temp = CHECK_ROW_FOR_K(*s_board, Dest, Start);
                if (temp == 1) Color = 'B';
                else if (temp == 2) Color = 'W';

                if (temp)
                {
                        int Remove_From[2];
                        int Remove_To[2];
                        FIND_INDEX_TO_REMOVE(*s_board, Start, Dest, Remove_From, Remove_To, 0);
                        REMOVE_PAWNS_BY_INDEX(s_board, Remove_From, Remove_To, Color);
                }
        }
}


// funckja sprawdza czy struktury mają takie same pola 
// zwraca 1 jeżeli tak
bool COMPARE_BOARDS(Board Orginal, Board New)
{
        if (Orginal.K != New.K || Orginal.S != New.S || Orginal.GB != New.GB || Orginal.GW != New.GW || Orginal.Active_Player != New.Active_Player)
        {
                return false;
        }
        if (Orginal.ABP != New.ABP || Orginal.AWP != New.AWP || Orginal.BR != New.BR || Orginal.WR != New.WR)
        {
                return false;
        }
        for (int row = 0; row < Orginal.S * 2 - 1; row++)
        {
                for (int col = 0; col < Orginal.S * 2 - 1; col++)
                {
                        if (Orginal.board[row][col] != New.board[row][col])
                        {
                                return false;
                        }
                }
        }
        return true;
}

void COPY_BOARD(Board& source, Board& destination)
{
        destination.S = source.S;
        destination.K = source.K;
        destination.GW = source.GW;
        destination.GB = source.GB;
        destination.WR = source.WR;
        destination.BR = source.BR;
        destination.Active_Player = source.Active_Player;
        destination.AWP = source.AWP;
        destination.ABP = source.ABP;
        destination.board = new char* [source.S * 2 - 1];
        for (int i = 0; i < source.S * 2 - 1; i++)
        {
                destination.board[i] = new char[source.S * 2 - 1];
                memcpy(destination.board[i], source.board[i], (source.S * 2 - 1) * sizeof(char));
        }
}

void PRINT_BOARD(Board s_board)
{
        cout << s_board.S << " " << s_board.K << " " << s_board.GW << " " << s_board.GB << endl;
        cout << s_board.WR << " " << s_board.BR << " " << s_board.Active_Player << endl;

        for (int x = 0; x < s_board.S * 2 - 1; x++)
        {

                if (x <= s_board.S - 1) // dla rzędów przed i na przekątnej
                {

                        for (int space_count = 1; space_count < s_board.S - x; space_count++)
                        {
                                cout << " ";
                        }

                        for (int symbol_count = 0; symbol_count < s_board.S + x; symbol_count++)
                        {
                                cout << s_board.board[s_board.S + x - 1 - symbol_count][symbol_count] << " ";
                        }
                }
                else
                {
                        for (int space_count = 0; space_count < x - s_board.S + 1; space_count++)
                        {
                                cout << " ";
                        }

                        for (int symbol_count = 0; symbol_count < s_board.S * 2 - 1 - (x - (s_board.S - 1)); symbol_count++)
                        {
                                cout << s_board.board[s_board.S * 2 - 2 - symbol_count][x - (s_board.S - 1) + symbol_count] << " ";
                        }
                }
                cout << endl;
        }
}


void GENERATE_MOVES(Board s_board, vector<Board> vector)
{
        int Start[2];
        int Dest[2];
        int x = 0;
        int y = 0;
        Board new_board;

        COPY_BOARD(s_board, new_board);

        // iteruje po wszystkich indeksach Start
        for (int i = 0; i < s_board.S * 6; i++)
        {
                if (i <= s_board.S * 2)
                {
                        Start[1] = i + 1;
                        if (i < s_board.S + 1)
                        {
                                Start[0] = 97;
                        }
                        else
                        {
                                x++;
                                Start[0] = 97 + x;
                        }
                        for (int a = 0; a < 2; a++)
                        {
                                if (Start[0] == 97)
                                {
                                        Dest[0] = 98;
                                        Dest[1] = Start[1] + a;
                                }
                                else
                                {
                                        Dest[0] = Start[0] + a;
                                        Dest[1] = Start[1] - 1 + a;
                                }

                                COPY_BOARD(s_board, new_board);

                                if (IS_MOVE_VALID(s_board, Start, Dest, 0))
                                {
                                        if (IS_SPACE_IN_ROW(s_board, Start, Dest))
                                        {
                                                COMMIT_MOVE(&new_board, Start, Dest);
                                                REMOVE_K_ROWS_FROM_BOARD(&new_board);

                                                if (vector.size() == 0)
                                                {
                                                        vector.push_back(new_board);                                                    
                                                        COPY_BOARD(s_board, new_board);
                                                }
                                                else
                                                {
                                                        int found = 0;
                                                        for (int w = 0; w < vector.size(); w++)
                                                        {
                                                                if (COMPARE_BOARDS(new_board, vector[w]))
                                                                {
                                                                        found = 1;
                                                                        break;
                                                                
                                                                }
                                                        }
                                                        if (!found)
                                                        {
                                                                vector.push_back(new_board);
                                                                COPY_BOARD(s_board, new_board);
                                                        }
                                                }
                                        }
                                }       
                        }
                }
                else if (i <= s_board.S * 4)
                {
                        y--;
                        if (i <= s_board.S * 3 - 1)
                        {
                                x++;
                                Start[0] = 97 + x;
                                Start[1] = s_board.S * 2 + 1 + y;
                        }
                        else
                        {
                                Start[0] = s_board.S * 2 + 97;
                                Start[1] = s_board.S * 2 + 1 + y;
                        }
                        if (Start[1] == 1) x = 0;
                        for (int a = 0; a < 2; a++)
                        {
                                if (Start[0] == s_board.S * 2 + 97)
                                {
                                        Dest[0] = s_board.S * 2 + 96;
                                        Dest[1] = Start[1] + a;
                                }
                                else
                                {
                                        Dest[0] = Start[0] - 1 + a;
                                        Dest[1] = Start[1] - a;
                                }
                                COPY_BOARD(s_board, new_board);

                                if (IS_MOVE_VALID(s_board, Start, Dest, 0))
                                {
                                        if (IS_SPACE_IN_ROW(s_board, Start, Dest))
                                        {
                                                COMMIT_MOVE(&new_board, Start, Dest);
                                                REMOVE_K_ROWS_FROM_BOARD(&new_board);

                                                if (vector.size() == 0)
                                                {
                                                        vector.push_back(new_board);                                            
                                                        COPY_BOARD(s_board, new_board);
                                                }
                                                else
                                                {
                                                        int found = 0;
                                                        for (int w = 0; w < vector.size(); w++)
                                                        {
                                                                if (COMPARE_BOARDS(new_board, vector[w]))
                                                                {
                                                                        found = 1;
                                                                        break;

                                                                }
                                                        }
                                                        if (!found)
                                                        {
                                                                vector.push_back(new_board);                                            
                                                                COPY_BOARD(s_board, new_board);
                                                        }
                                                }

                                        }
                                }
                        }
                }
                else
                {
                        x++;
                        Start[0] = s_board.S*2 + 97 - x;
                        Start[1] = 1;
                        for (int a = 0; a < 2; a++)
                        {
                                if (Start[0] >= s_board.S + 97)
                                {
                                        Dest[0] = Start[0] - a;
                                        Dest[1] = 2;
                                }
                                else
                                {
                                        Dest[0] = Start[0] + a;
                                        Dest[1] = 2;
                                }
                                COPY_BOARD(s_board, new_board);

                                if (IS_MOVE_VALID(s_board, Start, Dest, 0))
                                {
                                        if (IS_SPACE_IN_ROW(s_board, Start, Dest))
                                        {
                                                COMMIT_MOVE(&new_board, Start, Dest);
                                                REMOVE_K_ROWS_FROM_BOARD(&new_board);

                                                if (vector.size() == 0)
                                                {
                                                        vector.push_back(new_board);
                                                        COPY_BOARD(s_board, new_board);
                                                }
                                                else
                                                {
                                                        int found = 0;
                                                        for (int w = 0; w < vector.size(); w++)
                                                        {
                                                                if (COMPARE_BOARDS(new_board, vector[w]))
                                                                {
                                                                        found = 1;
                                                                        break;

                                                                }
                                                        }
                                                        if (!found)
                                                        {
                                                                vector.push_back(new_board);
                                                                COPY_BOARD(s_board, new_board);
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }

        cout << endl << vector.size() << "_UNIQUE_MOVES" << endl;
}


int main()
{
        Board s_board;

        bool error = false;
        bool exit = false;

        vector<Board> Board_vector;
        string line;

        while (!exit)
        {
                line.clear();
                while (!feof(stdin))
                {
                        char ch = getchar();
                        if (feof(stdin))
                        {
                                exit = true;
                                break;
                        }
                        if (ch == '\r' || ch == '\n') break;
                        line.push_back(ch);
                }

                if (line == "LOAD_GAME_BOARD")
                {
                        
                        s_board.board = nullptr;

                        error = false;
                        s_board.ABP = 0;
                        s_board.AWP = 0;

                        cin >> s_board.S >> s_board.K >> s_board.GW >> s_board.GB;
                        cin >> s_board.WR >> s_board.BR >> s_board.Active_Player;


                        //inicjalizacja planszy
                        s_board.board = new char* [s_board.S * 2 - 1];
                        for (int i = 0; i < s_board.S * 2 - 1; i++)
                        {
                                s_board.board[i] = new char[s_board.S * 2 - 1];
                        }

                        for (int x = 0; x < s_board.S * 2 - 1; x++)
                        {
                                for (int y = 0; y < s_board.S * 2 - 1; y++)
                                {
                                        s_board.board[x][y] = 32; // 32 -> spacja 
                                }
                        }   

                        
                        while (getchar() != 10);

                        char ch;

                        //uzupełnianie planszy
                        for (int x = 0; x < s_board.S * 2 - 1; x++)
                        {
                                line.clear();
                                
                                do 
                                {                                
                                        if (feof(stdin)) 
                                        {
                                                exit = true;
                                                break;
                                        }
                                        ch = getchar();

                                        if (ch == '_' || ch == 'W' || ch == 'B') line.push_back(ch);
                                        
                                } while (ch != 10);


                                if (x < s_board.S - 1)
                                {
                                        if (line.size() != s_board.S + x)
                                        {
                                                cout << endl << "WRONG_BOARD_ROW_LENGTH" << endl;
                                                error = true;
                                        }
                                }
                                else if (x == s_board.S - 1)
                                {
                                        if (line.size() != s_board.S * 2 - 1)
                                        {
                                                cout << endl << "WRONG_BOARD_ROW_LENGTH" << endl;
                                                error = true;
                                        }
                                }
                                else if (line.size() != s_board.S * 2 - 1 - x + s_board.S - 1)
                                {
                                        cout << endl << "WRONG_BOARD_ROW_LENGTH" << endl;
                                        error = true;
                                }

                                if (!error)
                                {
                                        for (int symbol = 0; symbol < line.size(); symbol++)
                                        {
                                                if (x <= s_board.S - 1)
                                                        s_board.board[s_board.S - 1 + x - symbol][symbol] = line[symbol];
                                                else
                                                        s_board.board[s_board.S * 2 - 2 - symbol][x - (s_board.S - 1) + symbol] = line[symbol];

                                                if (line[symbol] == 'W') s_board.AWP++;
                                                else if (line[symbol] == 'B') s_board.ABP++;
                                        }
                                }
                        }               
                        if (!error)
                        {
                                if (s_board.AWP > s_board.GW - s_board.WR)
                                {
                                        cout << endl << "WRONG_WHITE_PAWNS_NUMBER";
                                        error = true;
                                }
                                else if (s_board.ABP > s_board.GB - s_board.BR)
                                {
                                        cout << endl << "WRONG_BLACK_PAWNS_NUMBER";
                                        error = true;
                                }
                                else
                                {
                                        int counter = 0;
                                        //rzędy poziome
                                        for (int x = 0; x < s_board.S * 2 - 1; x++)
                                        {
                                                int Start[2];
                                                int Dest[2];
                                                if (x < s_board.S)
                                                {                                
                                                        Start[0] = 97; // 'a'
                                                        Start[1] = 1 + x;

                                                        Dest[0] = 98; //  'b'
                                                        Dest[1] = Start[1] + 1;
                                                }                                               
                                                else
                                                {
                                                        Start[0] = 94 + x; // 'b,c,...'
                                                        Start[1] = 1;

                                                        Dest[0] = Start[0] + 1;
                                                        Dest[1] = 2;
                                                }

                                                if (CHECK_ROW_FOR_K(s_board, Dest, Start))
                                                {
                                                        counter++;
                                                }                                       
                                        }

                                        //rzędy '///'
                                        for (int x = 0; x < s_board.S * 2 - 1; x++)
                                        {
                                                int Start[2];
                                                int Dest[2];

                                                Start[0] = 98 + x;
                                                Start[1] = 1;

                                                Dest[0] = 98 + x;
                                                Dest[1] = 2;

                                                if (CHECK_ROW_FOR_K(s_board, Dest, Start))
                                                {
                                                        counter++;
                                                }
                                        }

                                        //rzędy '\\\'
                                        for (int x = 0; x < s_board.S * 2 - 1; x++)
                                        {
                                                int Start[2];
                                                int Dest[2];
                                                if (x < s_board.S)
                                                {
                                                        Start[0] = 97; // 'a'
                                                        Start[1] = 2 + x;

                                                        Dest[0] = 98; //  'b'
                                                        Dest[1] = Start[1];
                                                }
                                                else
                                                {
                                                        Start[0] = 94 + x; // 'b,c,...'
                                                        Start[1] = 2 + x;

                                                        Dest[0] = Start[0] + 1;
                                                        Dest[1] = Start[1];
                                                }

                                                if (CHECK_ROW_FOR_K(s_board, Dest, Start))
                                                {
                                                        counter++;
                                                }
                                        }

                                        
                                        if (!counter)
                                        {
                                                cout << endl << "BOARD_STATE_OK" << endl;
                                                
                                        }
                                        else if (counter > 1)
                                        {
                                                cout << endl << "ERROR_FOUND_" << counter << "_ROWS_OF_LENGTH_K" << endl;
                                                error = true;
                                        }
                                        else
                                        {
                                                cout << endl << "ERROR_FOUND_1_ROW_OF_LENGTH_K" << endl;
                                                error = true;
                                        }
                                }
                        }
                }

                else if (line.substr(0, 7) == "DO_MOVE")
                {
                        char ch = ' ';

                        int count = std::count(line.begin(), line.end(), ch);   // zlicza spacje i rozróżnia przez to polecenie "DO_MOVE a5-b5" od polecenia "DO_MOVE a5-b5 b: e2 e3"

                        int Start_Index[2];  // gdzie położyć kamien [0] -> ascii pola [1] indeks pola 
                        int Dest_Index[2];   // gdzie go przesunąć [0] -> ascii pola [1] indeks pola 

                        size_t space_index = line.find(' ');

                        string cord = line.substr(space_index + 1);

                        Start_Index[0] = cord[0];

                        int Index = 0;

                        for (int i = 1; i < cord.size(); i++)
                        {
                                if (cord[i] == '-') break;
                                Index = Index * 10 + (cord[i] - 48);
                        }
                        Start_Index[1] = Index;

                        space_index = cord.find('-');
                        cord = cord.substr(space_index + 1);

                        Dest_Index[0] = cord[0];

                        Index = 0;

                        for (int i = 1; i < cord.size(); i++)
                        {
                                if (cord[i] == ' ') break;
                                Index = Index * 10 + (cord[i] - 48);
                        }
                        Dest_Index[1] = Index;

                        if (count == 1)
                        {
                                if (IS_MOVE_VALID(s_board, Start_Index, Dest_Index, 1))
                                {
                                        if (IS_SPACE_IN_ROW(s_board, Start_Index, Dest_Index))
                                        {
                                                COMMIT_MOVE(&s_board, Start_Index, Dest_Index);
                                                REMOVE_K_ROWS_FROM_BOARD(&s_board);
                                                cout << endl << "MOVE_COMMITTED" << endl;
                                        }
                                        else
                                        {
                                                cout << endl << "BAD_MOVE_ROW_IS_FULL" << endl;
                                        }
                                }
                        }
                        else
                        {
                                int Remove_To_Imput[2];
                                int Remove_From_Imput[2];

                                space_index = line.find(':');
                                cord = line.substr(space_index - 1);
                                char Color = cord[0];
                                cord = cord.substr(3);

                                space_index = cord.find(' ');
                                string cord_temp;
                                for (int i = 0; i < space_index; i++)
                                {
                                        cord_temp.push_back(cord[i]);
                                }
                                
                                Remove_From_Imput[0] = (int)cord[0];
                                Remove_From_Imput[1] = 0;

                                for (int i = 1; i < cord_temp.size(); i++)
                                {
                                        Remove_From_Imput[1] = Remove_From_Imput[1] * 10 + (cord_temp[i] - 48);
                                }

                                cord_temp = cord.substr(space_index + 1);
                                
                                Remove_To_Imput[0] = (int)cord_temp[0];
                                Remove_To_Imput[1] = 0;
                                for (int i = 1; i < cord_temp.size(); i++)
                                {
                                        Remove_To_Imput[1] = Remove_To_Imput[1] * 10 + (cord_temp[i] - 48);
                                }
                                int Remove_From[2];
                                int Remove_To[2];
                                int vector_y;
                                int vector_x;
                                bool reverse = false;
                                if (Remove_From_Imput[0] > s_board.S - 1 + 98)  // jezeli kolumna startowa jest za przekątną 
                                {
                                        reverse = true;
                                        vector_y = Remove_From_Imput[1] - Remove_To_Imput[1] + (Remove_From_Imput[0] - 98 - (s_board.S - 1));
                                        if (vector_y < 0) vector_y = -1;
                                        else if (vector_y > 0) vector_y = 1;
                                        vector_x = Remove_To_Imput[0] - Remove_From_Imput[0];
                                        if (vector_x < 0) vector_x = -1;
                                        else if (vector_x > 0) vector_x = 1;
                                }
                                else
                                {
                                        if (Remove_To_Imput[0] > s_board.S - 1 + 98) // jezeli kolumna końcowa jest za przekątną
                                        {
                                                int transfer = Remove_To_Imput[0] - 98 - (s_board.S - 1);
                                                vector_y = Remove_From_Imput[1] - (Remove_To_Imput[1] + transfer);
                                        }
                                        else vector_y = Remove_From_Imput[1] - Remove_To_Imput[1];
                                        if (vector_y < 0) vector_y = -1;
                                        else if (vector_y > 0) vector_y = 1;
                                        vector_x = Remove_To_Imput[0] - Remove_From_Imput[0];
                                        if (vector_x < 0) vector_x = -1;
                                        else if (vector_x > 0) vector_x = 1;
                                }

                                int Start[2];
                                int Dest[2];

                                Start[0] = Remove_From_Imput[0];
                                Start[1] = Remove_From_Imput[1];

                                int col = Start[0]-98;
                                int row;
                                int transfer;
                                if (!reverse)
                                {
                                        row = s_board.S * 2 - Start[1];
                                }
                                else
                                {
                                        transfer = Start[0] - 98 - (s_board.S - 1);
                                        row = s_board.S * 2 - 2 - transfer + (2 - Start[1]);
                                }

                                while (true)
                                {
                                        row -= vector_y;
                                        col -= vector_x;
                                        transfer = col - (s_board.S - 1);

                                        if (row < 0 || row > s_board.S*2 - 2 || col < 0 || col > s_board.S * 2 - 2)
                                        {
                                                Start[0] = 98 + col;
                                                if (!reverse)
                                                {
                                                        Start[1] = s_board.S * 2 - row;
                                                }
                                                else
                                                {
                                                        Start[1] = s_board.S * 2 - transfer - row;
                                                }
                                                row += vector_y;
                                                col += vector_x;
                                                Dest[0] = 98 + col;
                                                if (!reverse)
                                                {
                                                        Dest[1] = s_board.S * 2 - row;
                                                }
                                                else
                                                {
                                                        transfer = col - (s_board.S - 1);
                                                        Dest[1] = s_board.S * 2 - transfer - row;
                                                }
                                                break;
                                        }
                                        if (s_board.board[row][col] == ' ')
                                        {
                                                Dest[0] = 98 + col;
                                                if (!reverse)
                                                {
                                                        Dest[1] = s_board.S * 2 - row;
                                                }
                                                else
                                                {
                                                        Dest[1] = s_board.S * 2 - transfer - row;
                                                }
                                                row += vector_y;
                                                col += vector_x;
                                                Start[0] = 98 + col;
                                                if (!reverse)
                                                {
                                                        Start[1] = s_board.S * 2 - row;
                                                }
                                                else
                                                {
                                                        Start[1] = s_board.S * 2 - transfer - row;
                                                }
                                                break;
                                        }
                                        else
                                        {
                                                Start[0] = 98 + col;
                                                if (!reverse)
                                                {
                                                        Start[1] = s_board.S * 2 - row;
                                                }
                                                else
                                                {
                                                        Start[1] = s_board.S * 2 - transfer - row;
                                                }
                                        }
                                }                       
                                int color;

                                if (Color == 'b') color = 1;
                                else color = 2;                 

                                if (IS_MOVE_VALID(s_board, Start_Index, Dest_Index, 1))
                                {
                                        if (IS_SPACE_IN_ROW(s_board, Start_Index, Dest_Index))
                                        {
                                                COMMIT_MOVE(&s_board, Start_Index, Dest_Index);

                                                if (CHECK_ROW_FOR_K(s_board, Dest, Start) != color)
                                                {
                                                        cout << endl << "WRONG_COLOR_OF_CHOSEN_ROW" << endl;
                                                }
                                                else
                                                {
                                                        FIND_INDEX_TO_REMOVE(s_board, Start, Dest, Remove_From, Remove_To, 1);
                                                        int Converted_From_Imput[2];
                                                        int Converted_To_Imput[2];
                                                        Converted_From_Imput[1] = CONVERT_INDEX_COL(Remove_From_Imput, 0);
                                                        Converted_From_Imput[0] = CONVERT_INDEX_ROW(Remove_From_Imput, 0, s_board);
                                                        Converted_To_Imput[1] = CONVERT_INDEX_COL(Remove_To_Imput, 0);
                                                        Converted_To_Imput[0] = CONVERT_INDEX_ROW(Remove_To_Imput, 0, s_board);
                                                        if (Converted_From_Imput[0] != Remove_From[0] || Converted_From_Imput[1] != Remove_From[1] || Converted_To_Imput[0] != Remove_To[0] || Converted_To_Imput[0] != Remove_To[0]) // indeksy się nie zgadzają 
                                                        {
                                                                cout << endl << "WRONG_INDEX_OF_CHOSEN_ROW" << endl;
                                                        }
                                                        else
                                                        {
                                                                FIND_INDEX_TO_REMOVE(s_board, Start, Dest, Remove_From, Remove_To, 0);
                                                                REMOVE_PAWNS_BY_INDEX(&s_board, Remove_From, Remove_To, Color);
                                                                cout << endl << "MOVE_COMMITTED" << endl;
                                                        }
                                                }                       
                                        }
                                        else
                                        {
                                                cout << endl << "BAD_MOVE_ROW_IS_FULL" << endl;
                                        }
                                }               
                        }
                }

                else if (line == "PRINT_GAME_BOARD")
                {
                        if (error == true)
                        {
                                cout <<endl<< "EMPTY_BOARD" << endl;
                        }
                        else
                        {
                                PRINT_BOARD(s_board);
                        }
                }
                else if (line == "GEN_ALL_POS_MOV_NUM")
                {
                        //wykonuje wszytkie możliwe ruchy i zapisuje do wektora te które się już tam nie znajdują (unikalne)
                        GENERATE_MOVES(s_board, Board_vector);
                        Board_vector.clear();
                }
        }
        
        return 0;
}

