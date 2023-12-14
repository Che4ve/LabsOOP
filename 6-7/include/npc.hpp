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

constexpr unsigned int ELF_ATTACK_RANGE   = 6;
constexpr unsigned int BEAR_ATTACK_RANGE  = 8;
constexpr unsigned int THIEF_ATTACK_RANGE = 5;

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

        virtual std::string getTypeStr() const = 0;

        virtual void accept(IVisitor* v) {};

        void roam() {
            std::srand(static_cast<unsigned>(std::time(nullptr)) + std::rand());
            x += (std::rand() % 3) - 1;
            y += (std::rand() % 3) - 1;
        }

        void die() { _alive = false; }

        void attack(NPC* target) { target->die(); }

        virtual bool isCompatibleWith(NPC* target) = 0;

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

        friend NPC* deserialize(std::string &line);

        friend std::ostream& operator<<(std::ostream& os, const NPC& n);

    public:
        int x;
        int y;

        std::string _name{};
        bool _alive{ true };
        int _attackRange{ 0 };

};



class IVisitor {
    public:
        virtual void visit(NPC* npc) {};
};

class Elf : public NPC {
public:
    Elf(int x, int y, std::string& name) : NPC(x, y, name) {
        setAttackRange( ELF_ATTACK_RANGE );
    }
    //~Elf() override {}
    NPCType getType() const override { return ELF; } 
    std::string getTypeStr() const override { return "Elf"; }
    
    void accept(IVisitor* v) override { v->visit(this); }

    bool isCompatibleWith(NPC* target) override { 
        return target->getType() == THIEF;
    }
};

class Bear : public NPC {
public:
    Bear(int x, int y, std::string& name) : NPC(x, y, name) {
        setAttackRange( BEAR_ATTACK_RANGE );
    }
    //~Bear() override {}
    NPCType getType() const override { return BEAR; } 
    std::string getTypeStr() const override { return "Bear"; }

    void accept(IVisitor* v) override { v->visit(this); }

    bool isCompatibleWith(NPC* target) override { 
        return target->getType() == ELF;
    }
};

class Thief : public NPC {
public:
    Thief(int x, int y, std::string& name) : NPC(x, y, name) {
        setAttackRange( THIEF_ATTACK_RANGE );
    }
    //~Thief() override {}
    NPCType getType() const override { return THIEF; } 
    std::string getTypeStr() const override { return "Thief"; }

    void accept(IVisitor* v) override { v->visit(this); }

    bool isCompatibleWith(NPC* target) override { 
        return target->getType() == THIEF;
    }
};

class NPCFightVisitor : public IVisitor {
    public:
        void visit(NPC* npc) override {
            npc->roam();
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

std::ostream& operator<<(std::ostream& os, const NPC& npc) {
    std::string name = npc.getName();
    std::string type = npc.getTypeStr();
    int x = npc.x;
    int y = npc.y;
    os << "type: " << type << ", name: " << name << ", x: " << x << ", y: " << y;
    return os;
}

NPC* deserialize(std::string &line) {
    NPCFactory npcFactory; 
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
        return npcFactory.createNPC(static_cast<NPCType>(type), x, y, name);
    }      
    return nullptr;
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
                throw std::runtime_error("Invalid line format in CSV.");
            }
        }
    } else {
        throw std::runtime_error("Error opening NPC file.");
    }
    return npcs;
}

void saveNPCsToFile(const std::string& filename, const std::vector<NPC*>& npcs) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (NPC* npc : npcs) {
            npc->serialize(file);
        }
        file.close();
    } else {
        std::cerr << "Error opening file " << filename << std::endl;
    }
}
