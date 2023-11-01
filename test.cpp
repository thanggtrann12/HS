#include <iostream>
#include <vector>
#include <sstream>
const char DELIMITER = '\v';
typedef std::vector<std::string> card_template_t;
const card_template_t CARD_TEMPLATE_MINION_WITH_ABILITY =
      {"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
       "┃    ~NNNNNNNNNNNNNNNNNNNNN~    ┃",
       "┠───────────────┬───────────────┨",
       "┃ ~TTTTTTT~     │ ~SSSSSSSSS~   ┃",
       "┠───────────────┴───────────────┨",
       "┃   ~KKKKKKKKKKKKKKKKKKKKK      ┃",
       "┃   KKKKKKKKKKKKKKKKKKKKKKKKK   ┃",
       "┃              KKK~             ┃",
       "┠─ATK─┐                   ┌──HP─┨",
       "┃  ~A~│                   │~H~  ┃",
       "┗━━━━━┷━━━━━━━━━━━━━━━━━━━┷━━━━━┛"};

const card_template_t CARD_TEMPLATE_MINION_NO_ABILITY =
      {"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
       "┃    ~NNNNNNNNNNNNNNNNNNNNN~    ┃",
       "┠───────────────────────────────┨",
       "┃ ~TTTTTTTTTTTTTTTTTTTTTTTTTTT~ ┃",
       "┠───────────────────────────────┨",
       "┃   ~KKKKKKKKKKKKKKKKKKKKKK     ┃",
       "┃   KKKKKKKKKKKKKKKKKKKKKKKKK   ┃",
       "┃              KKK~             ┃",
       "┠─ATK─┐                   ┌──HP─┨",
       "┃  ~A~│                   │~H~  ┃",
       "┗━━━━━┷━━━━━━━━━━━━━━━━━━━┷━━━━━┛"};
const std::vector<std::string> CENTRE_GRAPHIC = 
      {"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
       "┃                                                                                                                                                                           ┃",
       "┃                                                                                                                                                                           ┃",
       "┃                                                                                                                                                                           ┃",
       "┃                                                                                                                                                                           ┃",
       "┃                                                                                                                                                                           ┃",
       "┃                                                                                                                                                                           ┃",
       "┃                                                                                                                                                                           ┃",
       "┃                                                                                                                                                                           ┃",
       "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"};

const std::string EXTERNAL_BORDER_CHAR_UP_DOWN =
      "║";

const std::string EXTERNAL_BORDER_CHAR_LEFT_RIGHT =
      "═";
const std::string EXTERNAL_BORDER_CHAR_TOP_LEFT =
      "╔";

const std::string EXTERNAL_BORDER_CHAR_TOP_RIGHT =
      "╗";

const std::string EXTERNAL_BORDER_CHAR_BOTTOM_LEFT =
      "╚";

const std::string EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT =
      "╝";
void replace_text_left(card_template_t &text,char flag,std::string new_text) {
  std::string::iterator sit = new_text.begin();
  bool start_replace = false;
  bool end_replace = false;
  for (card_template_t::iterator vit = text.begin(); vit != text.end(); ++vit) {
    for (std::string::iterator lit = vit->begin(); lit != vit->end(); ++lit) {
      if (*lit == DELIMITER && *(lit+1) == flag) {
        start_replace = true;
      } else if (*lit == DELIMITER) {
        end_replace = true;
      }
      if (start_replace && (*lit == flag || *lit == DELIMITER)) {
        if (sit != new_text.end()) {
          *lit = *sit;
          ++sit;
        } else {
          *lit = ' ';
        }
      }
      if (end_replace) {
        end_replace = false;
        start_replace = false;
      }
    }
  }
}

static void replace_text_right(card_template_t &text,char flag,std::string new_text) {
  std::string::reverse_iterator sit = new_text.rbegin();
  bool start_replace = false;
  bool end_replace = false;
  for (card_template_t::reverse_iterator vit = text.rbegin(); vit != text.rend(); ++vit) {
    for (std::string::reverse_iterator lit = vit->rbegin(); lit != vit->rend(); ++lit) {
      if (*lit == DELIMITER && *(lit+1) == flag) {
        start_replace = true;
      } else if (*lit == DELIMITER) {
        end_replace = true;
      }
      if (start_replace && (*lit == flag || *lit == DELIMITER)) {
        if (sit != new_text.rend()) {
          *lit = *sit;
          ++sit;
        } else {
          *lit = ' ';
        }
      }
      if (end_replace) {
        end_replace = false;
        start_replace = false;
      }
    }
  }
}

void prepare_for_replace(card_template_t &text) {
  for (card_template_t::iterator it=text.begin();it != text.end();++it) {
    for (std::string::iterator sit = it->begin();sit != it->end();++sit) {
      if (*sit == '~') *sit = DELIMITER;
    }
  }
}
card_template_t display_minion_general(card_template_t out,std::string name,int attack,int health,std::string skill, std::string status) {
  std::ostringstream oss;
  prepare_for_replace(out);
  replace_text_left(out,'N',name);
  replace_text_right(out,'T',"Minion");
  replace_text_right(out,'S',status);
  oss.str("");
  oss << attack;
  replace_text_left(out,'A',oss.str());
  oss.str("");
  oss << health;
  replace_text_right(out,'H',oss.str());
  replace_text_left(out,'K',skill);
  oss.str("");
  return out;
}
void display_table(std::vector<std::vector<std::string>> hand)
{
  size_t maxRows = 0;
  for (const std::vector<std::string>& row : hand) {
    if (row.size() > maxRows) {
      maxRows = row.size();
    }
  }
  for (size_t i = 0; i < maxRows; i++) {
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN<< "  ";
    for (const std::vector<std::string>& row : hand) {
      if (i < row.size()) {
        std::cout << row[i] << "  ";
      }
    }
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN<< "  " << std::endl;
	}
}
int main()
{
  std::vector<std::vector<std::string>> displayHand1;
  card_template_t out = display_minion_general(CARD_TEMPLATE_MINION_WITH_ABILITY,"Ragnaros the Firelord",1,3,"A minion with 1HP and 1 Attack", "INACTIVE");
  card_template_t out2 = display_minion_general(CARD_TEMPLATE_MINION_NO_ABILITY,"Ragnaros the Firelord",1,3,"Destroy a random minion of the opposite player", "");
  card_template_t out3 = display_minion_general(CARD_TEMPLATE_MINION_WITH_ABILITY,"Ragnaros the Firelord",1,3,"Provides all alliance minions with attack bonus [1]", "INACTIVE");
  card_template_t out4 = display_minion_general(CARD_TEMPLATE_MINION_NO_ABILITY,"Ragnaros the Firelord",1,3,"Destroy a random minion of the opposite player", "");
  card_template_t out5 = display_minion_general(CARD_TEMPLATE_MINION_NO_ABILITY,"Ragnaros the Firelord",1,3,"On dead, deals 3 damage to both hero", "");
  displayHand1.emplace_back(out);
  displayHand1.emplace_back(out2);
  displayHand1.emplace_back(out3);
  displayHand1.emplace_back(out4);
  displayHand1.emplace_back(out5);
  std::cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
	for(unsigned int i = 0; i < 177; i++){
		std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
	}
	std::cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;
	display_table(displayHand1);
	for(unsigned int i = 0; i < CENTRE_GRAPHIC.size(); i++){
		std::cout <<EXTERNAL_BORDER_CHAR_UP_DOWN<<"  "<<CENTRE_GRAPHIC[i]<<"  "<<EXTERNAL_BORDER_CHAR_UP_DOWN<< std::endl;
	}
  display_table(displayHand1);

	std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
	for(unsigned int i = 0; i < 177; i++){
		std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
	}
	std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;


  return 0;
}