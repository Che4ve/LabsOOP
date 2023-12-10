#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <random>
#include <memory>
/*
Эльфы убивают разбойников 
Разбойники убивают разбойников 
Медведь убивает Эльфов
*/
class NPC;
class Elf;
class Bear;
class Thief;

class NPCState;
class NPCFactory;
class IVisitor;
class NPCFightVisitor;

enum NPCType {
    ELF,
    BEAR,
    THIEF
};

class NPC {
    public:
        NPC(std::string& name) : 
            x(0), y(0), 
            _name(name) {}

        NPC(int x, int y, std::string& name) : 
            x(x), y(y), 
            _name(name) {}

        virtual ~NPC() = default;

        virtual NPCType getType() const = 0;

        virtual void accept(IVisitor* v) {};

        void moveRandomly(bool move) {
            if (move) {
                _state.roam();
            } else {
                _state.idle();
            }
        }

        void die() {
            _alive = false;
        }

        virtual bool attack(NPC* target) = 0;

        std::string getName() const { return _name; }

        void setAttackRange(int range) { _attackRange = range; }

        int getAttackRange() const { return _attackRange; }

        int getDistance2(NPC* target) { 
            return std::sqrt(std::pow(target->x - x, 2) + std::pow(target->y - y, 2));
        }

        bool isAlive() const { return _alive; }

        // Сериализация NPC в файл
        void serialize(std::ostream& os) const {
            os << getType() << ',' << getName() << ',' << x << ',' << y << '\n';
        }

    public:
        int x;
        int y;

    private:
        class NPCState {
        private:
            NPC* _npc;

        public:
            NPCState(NPC* npc) : _npc(npc) {}

            void idle() { return; }

            void roam() {
                std::srand(static_cast<unsigned>(std::time(nullptr)) + std::rand());
                _npc->x += (std::rand() % 3) - 1;
                _npc->y += (std::rand() % 3) - 1;
            }
        };
        std::string _name;
        NPCState _state{ this };
        bool _alive{ true };
        int _attackRange;

};

class IVisitor {
    public:
        virtual void visit(NPC* npc) {};
};

class Elf : public NPC {
public:
    Elf(int x, int y, std::string& name) : NPC(x, y, name) {
        setAttackRange(5);
    }
    //~Elf() override {}
    NPCType getType() const override { return ELF; } 
    void accept(IVisitor* v) override { v->visit(this); }
    
    bool attack(NPC* target) override {
        int distance = std::sqrt(std::pow(target->x - x, 2) + std::pow(target->y - y, 2));

        if (distance <= getAttackRange() && target->getType() == THIEF) {
            target->die();
            return true;
        }
        return false;
    }
};

class Bear : public NPC {
public:
    Bear(int x, int y, std::string& name) : NPC(x, y, name) {
        setAttackRange(10);
    }
    //~Bear() override {}
    NPCType getType() const override { return BEAR; } 
    void accept(IVisitor* v) override { v->visit(this); }

    bool attack(NPC* target) override {
        int distance = std::sqrt(std::pow(target->x - x, 2) + std::pow(target->y - y, 2));

        if (distance <= getAttackRange() && target->getType() == ELF) {
            target->die();
            return true;
        }
        return false;
    }
};

class Thief : public NPC {
public:
    Thief(int x, int y, std::string& name) : NPC(x, y, name) {
        setAttackRange(3);
    }
    //~Thief() override {}
    NPCType getType() const override { return THIEF; } 
    void accept(IVisitor* v) override { v->visit(this); }

    bool attack(NPC* target) override {
        int distance = std::sqrt(std::pow(target->x - x, 2) + std::pow(target->y - y, 2));

        if (distance <= getAttackRange() && target->getType() == THIEF) {
            target->die();
            return true;
        }
        return false;
    }
};

class NPCFightVisitor : public IVisitor {
    public:
        void visit(NPC* npc) override {
            npc->moveRandomly(true);
        }
};

// Фабричный паттерн (интерфейс NPC)
class NPCFactory {
    public: NPC* createNPC(NPCType type, int x, int y, std::string& name) {
        switch (type) {
            case ELF:
                return new Elf(x, y, name);
                break;
            case BEAR:
                return new Bear(x, y, name);
                break;
            case THIEF:
                return new Thief(x, y, name);
                break;
            default:
                return NULL;
        }
    }
};

// Функция для сохранения NPC в файл
void saveNPCToFile(NPC* npc, const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        npc->serialize(file);
        file.close();
    } else {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
    }
}

std::vector<NPC*> loadNPCsFromFile(const std::string& filename) {
    std::vector<NPC*> npcs;
    std::ifstream file(filename);
    if (file.is_open()) {
        NPCFactory npcFactory;
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string token;
            std::vector<std::string> tokens;
            
            // Split the line by comma to extract CSV values
            while (std::getline(iss, token, ',')) {
                tokens.push_back(token);
            }
            
            // Assuming the CSV format is: type, name, x, y
            if (tokens.size() == 4) {
                int type = std::stoi(tokens[0]);
                std::string name = tokens[1];
                int x = std::stoi(tokens[2]);
                int y = std::stoi(tokens[3]);
                
                // Create NPC using NPCFactory based on parsed data
                NPC* newNPC = npcFactory.createNPC(static_cast<NPCType>(type), x, y, name);
                npcs.push_back(newNPC);
            } else {
                std::cerr << "Invalid line format in CSV." << std::endl;
                // Handle invalid line format
            }
        }
    } else {
        std::cerr << "Error opening NPC file " << filename << std::endl;
    }
    return npcs;
}
