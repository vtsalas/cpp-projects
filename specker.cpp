#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Move {
public:
    //Take sc coins from heap sh and put tc to heap th.
    //εδώ είναι η στιγμή που καλώ τον constructor όπως σε κάθε κλάση
    Move(int sh, int sc, int th, int tc) {
        source_heap = sh;
        source_coins = sc;
        target_heap = th;
        target_coins = tc;
    }

    int getSource() const {
        return source_heap;
    }

    int getSourceCoins() const {
        return source_coins;
    }    

    int getTarget() const {
        return target_heap;
    }

    int getTargetCoins() const {
        return target_coins;
    }

    friend ostream & operator << (ostream &out, const Move &move) {
        if (move.target_coins > 0) {
        out << "takes " << move.source_coins << " coins from heap " << move.source_heap << " and puts " << move.target_coins << " coins to heap " << move.target_heap;
        }
        else {
             out << "takes " << move.source_coins << " coins from heap " << move.source_heap << " and puts nothing";
        }
        return out; 
    }
private:
    int source_heap;
    int source_coins;
    int target_heap;
    int target_coins;

};

class State {
public:
    //State with h heaps , where the i-h heap starts with c[i] coins
    //A total of n players are in the game, numbered from 0 to n-1,
    //and player 0 is the first to play.
    State(int h, const int c[], int n) {
        heaps = h;
        players = n;
        coins = new int[h];

        for(int i=0; i < h; i++) {
            coins[i] = c[i];
        }

        playing = 0;

    }

    ~State() {
        delete[] coins;
    }

    void next(const Move &move) {
        int sh = move.getSource();
        int sc = move.getSourceCoins();
        int th = move.getTarget();
        int tc = move.getTargetCoins();

        if (sh < 0 || sh >= heaps) throw logic_error("invalid heap");
        if (sc <= 0 || sc > coins[sh]) throw logic_error("invalid coins");

        coins[sh] = coins[sh] - sc;

        if (tc > 0 && (th < 0 || th >= heaps)) throw logic_error("invalid heap");
        if (tc < 0 || tc >= sc) throw logic_error("invalid coins");

        if(tc > 0) {
        coins[th] = coins[th] + tc;
        }

        //καλή μαγκιά για κυκλική κίνηση, το playing αυξάνεται κανονικά κατά ένα μεχρι να γίνει
        //ίσο με το players όπου το playing % players = 0;
        playing = (playing + 1) % players;
    }

    bool winning() const {
        for (int i = 0; i < heaps; i++) {
            if (coins[i] > 0) {
                return false;
            }
        }
        return true;
            
        }

    int getHeaps() const {
        return heaps;
    }
    int getCoins(int h) const {
        if (h < 0 || h >= heaps) throw logic_error("invalid heap");
        return coins[h];
    } 
    int getPlayers() const {
        return players;
    }
    int getPlaying() const {
        return playing;
    }

    friend ostream & operator << (ostream &out, const State &state) {
        for(int i=0; i<state.heaps; i++){
            out << state.coins[i];
             if (i < state.heaps-1) {
                out << ", ";
            }
        }
        out << " with " << state.playing << "/" << state.players << " playing next";
        return out;
    }

    
private:
    int playing;
    int heaps;
    int players;
    int* coins;
};

class Player {
public:
    Player(const string &n) {
        name = n;
    }
    virtual ~Player() {};

    virtual const string & getType() const = 0;
    virtual Move play(const State &s) = 0;

    friend ostream & operator << (ostream &out, const Player &player) {
        out << player.getType() << " player " << player.name;
        return out;
    }


private:
    string name;
};

class GreedyPlayer : public Player {
public:

    //o constructor του GreedyPlayer, παίρνει το όνομα n και το πετάει κατευθείαν στον player,
    //έπειτα δηλώνει το type ως greedy
    GreedyPlayer(const string &n) : Player(n) {
        type = "Greedy";
    }

    const string & getType() const override {
        return type;
    }

    Move play(const State &s) override {
        int max_coins = 0;
        int best_heap = 0;

        //Τωρα ο Greedy πρέπει να βρει τον σωρό με τα περισσότερα νομίσματα
        for(int i = 0; i<s.getHeaps(); i++) {
            if (s.getCoins(i) > max_coins) {
                max_coins = s.getCoins(i);
                best_heap = i;
            }
        }

        //αφού βρήκε τον σωρό με τα περισσότερα χρήματα (best_heap) ξέρει ποιο είναι το source_heap
        //και τα source_coins (max_coins) αφού δεν βάζει κανένα πίσω τα άλλα δεν μας ενδιαφέρουν και
        //τελικά καλούμε την move!
        return Move(best_heap, max_coins, 0, 0);
    }


private:
    string type;

};

class SpartanPlayer : public Player {
public:

    //o constructor του SpartanPlayer, παίρνει το όνομα n και το πετάει κατευθείαν στον player,
    //έπειτα δηλώνει το type ως spartan
    SpartanPlayer(const string &n) : Player(n) {
        type = "Spartan";
    }

    const string & getType() const override {
        return type;
    }

    Move play(const State &s) override {
        int max_coins = 0;
        int best_heap = 0;

        //Τωρα ο Spartan πρέπει να βρει τον σωρό με τα περισσότερα νομίσματα
        for(int i = 0; i<s.getHeaps(); i++) {
            if (s.getCoins(i) > max_coins) {
                max_coins = s.getCoins(i);
                best_heap = i;
            }
        }

        //αφού βρήκε τον σωρό με τα περισσότερα χρήματα (best_heap) ξέρει ποιο είναι το source_heap
        //και τα source_coins που είναι 1. Αφού δεν επιστρέφει τίποτα τα υπόλοιπα δεν μας εδνιαφέρουν
        //τελικά καλούμε την move!
        return Move(best_heap, 1, 0, 0);
    }


private:
    string type;

};

class SneakyPlayer : public Player {
public:

    //o constructor του SneakyPlayer, παίρνει το όνομα n και το πετάει κατευθείαν στον player,
    //έπειτα δηλώνει το type ως sneaky
    SneakyPlayer(const string &n) : Player(n) {
        type = "Sneaky";
    }

    const string & getType() const override {
        return type;
    }

    Move play(const State &s) override {
        int min_coins = 999999999;
        int worst_heap = 0;

        //Τωρα ο Sneaky πρέπει να βρει τον σωρό με τα λιγότερα νομίσματα
        for(int i = 0; i<s.getHeaps(); i++) {
            if (s.getCoins(i) < min_coins && s.getCoins(i) > 0) {
                min_coins = s.getCoins(i);
                worst_heap = i;
            }
        }

        //αφού βρήκε τον σωρό με τα περισσότερα χρήματα (best_heap) ξέρει ποιο είναι το source_heap
        //και τα source_coins (max_coins) αφού δεν βάζει κανένα πίσω τα άλλα δεν μας ενδιαφέρουν και
        //τελικά καλούμε την move!
        return Move(worst_heap, min_coins, 0, 0);
    }


private:
    string type;

};

class RighteousPlayer : public Player {
public:
    RighteousPlayer(const string &n) : Player(n) {
        type = "Righteous";
    }

    const string & getType() const override { return type; }

    Move play(const State &s) override {
        int max_coins = 0;
        int best_heap = 0;
        int min_coins = 999999999;
        int worst_heap = 0;
    
     //βρίσκουμε τον σωρό με τα περισσότερα νομίσματα
        for(int i = 0; i<s.getHeaps(); i++) {
            if (s.getCoins(i) > max_coins) {
                max_coins = s.getCoins(i);
                best_heap = i;
            }
        }

    //βρίσκουμε τον σωρό με τα λιγότερα νομίσματα
        for(int i = 0; i<s.getHeaps(); i++) {
            if (s.getCoins(i) < min_coins) {
                min_coins = s.getCoins(i);
                worst_heap = i;
            }
        }
    //μαγκιά γιατί η διαίρεση με ints δεν κρατάει το 0.5, άρα αν είχαμε 16 θα έκανε 16+1/2 = 8.5 και θα κράταγε το 8 σωστό
    //αν είχαμε 17 θα έκανε 17+1/2 = 9 που είναι και αυτό που θέλουμε
    int sc = (max_coins+1)/2;
    int tc = sc - 1;
    
        return Move(best_heap, sc, worst_heap, tc);

    }



private:
    string type;

};

class Game {
public:
    //constructor  της game
    Game(int heaps, int players) {
        max_players = players;
        max_heaps = heaps;

        heap_coins = new int[max_heaps];

        player_list = new Player*[max_players];

        current_heaps = 0;
        current_players = 0;
    }
    ~Game() {
        for(int i=0; i<current_players; i++) {
            delete player_list[i];
        }

        delete[] player_list;
        delete[] heap_coins;
    }

    void addHeap(int coins) {
        if (current_heaps >= max_heaps) {
            throw logic_error("Too many heaps!");
        }
        else {
            heap_coins[current_heaps] = coins;
            current_heaps++;
        }
    }
    void addPlayer(Player *player) {
        if(current_players >= max_players) {
            throw logic_error("Too many players!");
        }
        else{
            player_list[current_players] = player;
            current_players++;
        }
    }
    void play(ostream &out){
        //αρχικά πρέπει να στήσω το τραπέζι, άρα φτιάχνω ένα αντικείμενο state με όσα χρειάζεται
        State state(current_heaps, heap_coins, current_players);

        int last_player = 0; //ο τελευταίος παίκτης που έπαιξε σε κάθε γύρο

        //άπειρος βρόχος του παιχνιδιού, όσο δεν υπάρχει νικητής
        while(!state.winning()) {
            out << "State: " << state << endl;
        

        last_player = state.getPlaying();

        out << *player_list[last_player] << " ";

        Move move = player_list[last_player]->play(state);

        out << move << endl;

        state.next(move);
        }

        out << "State: " << state << endl;

        out << *player_list[last_player] << " wins" << endl;
    }

    int getPlayers() const {
        return current_players;
    }

    const Player *getPlayer(int p) const {
        if (p < 0 || p >= current_players) {
        throw logic_error("Invalid player index");
    }
    
    //Δίνουμε τον pointer από τον πίνακα μας
    return player_list[p];
    }
    

private:
    int max_players; //οι παίκτες που χωράει το παιχνίδι
    int max_heaps; //οι σωροί που χωράει το παιχνίδι

    int current_heaps; //πόσους σωρούς έχουμε βάλει μέχρι τώρα
    int current_players; //πόσους παίκτες έχουμε βάλει μέχρι τώρα

    int *heap_coins; //εδώ νοικιάζω τον χώρο για να ξέρω πόσα coins θα έχει ο κάθε heap

    Player** player_list;
};

int main() {
    // Φτιάχνουμε ένα παιχνίδι με 3 σωρούς και 4 παίκτες
    Game specker(3, 4);

    // Προσθέτουμε τα αρχικά νομίσματα στους σωρούς
    specker.addHeap(10);
    specker.addHeap(20);
    specker.addHeap(17);

    // Βάζουμε τους παίκτες να καθίσουν στο τραπέζι με τη σειρά
    specker.addPlayer(new SneakyPlayer("Tom"));
    specker.addPlayer(new SpartanPlayer("Mary"));
    specker.addPlayer(new GreedyPlayer("Alan"));
    specker.addPlayer(new RighteousPlayer("Robin"));

    // Ξεκινάμε το παιχνίδι και τυπώνουμε τα αποτελέσματα στην οθόνη (cout)
    specker.play(cout);

    return 0;
}