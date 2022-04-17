#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
using std::vector;using std::string;

class Recipe{
    std::string name_;
    int servings_;
    std::vector<std::vector<std::string>> ingredients_;
    std::vector<std::string> instructions_;

    public:
    Recipe(std::string n,int s){
        name_ = n;
        servings_ = s;
    }

    //values can consist of whole (4), fractions(3/4), mixed (3-4/5), improper(9/4).
    //All values when written to an ostream must be in reduced-mixed form (3-9/2 should become 7-1/2).
    void AddIngredient(std::string ingre_str){
        std::string value_str,unit,ingredient_name, full_ingredient_name;
        std::vector<std::string> ingredient_vec;
        std::istringstream iss(ingre_str);

        //separate ingredient str into three parts
        iss >> value_str >> unit;
        while (iss >> ingredient_name){
            full_ingredient_name += ingredient_name + " ";
        }
        full_ingredient_name.pop_back(); //remove extra whitespace at the end

        //put the three parts into one ingredient vector
        ingredient_vec.push_back(value_str);
        ingredient_vec.push_back(unit);
        ingredient_vec.push_back(full_ingredient_name);

        //add in this ingredient vec with all the other ingredient vec
        ingredients_.push_back(ingredient_vec);

    }    

    // SetInstructions accepts a (possibly multiline) string denoting
    // instructions for the recipe. This string may have blank lines, 
    // leading whitespace, and/or trailing whitespace on each line. 
    // This whitespace should be removed when a Recipe is written to an ostream.
    //r.SetInstructions("Cut and put in mouth");
    void SetInstructions(std::string instr_str){
        std::string word, new_instr_str;
        std::istringstream iss(instr_str);

        //account for whitespace
        while (iss >> word){
            new_instr_str += word + " ";
        }
        new_instr_str.pop_back(); //remove extra whitespace at the end

        //add in this instruction with all the other instructions  
        instructions_.push_back(new_instr_str);
    }

    //support the operator<< to write to an ostream. Please see the test cases or below for examples of the specific formatting required.
    friend std::ostream & operator<<(std::ostream & o, const Recipe & recipe){
        int ingredient_size(recipe.ingredients_.size()),instruction_size(recipe.instructions_.size()),ingredient_row_size;

        o << "Recipe for: " << recipe.name_ << std::endl;
        o << "Serves " << recipe.servings_ << std::endl;

        //ingredients
        o << "Ingredients:" << std::endl;
        for (int i = 0; i < ingredient_size; i++) {
            ingredient_row_size = recipe.ingredients_[i].size();
            for (int j = 0; j < ingredient_row_size; j++){
                if (j==ingredient_row_size-1){
                    o << recipe.ingredients_[i][j];
                }
                else{
                    o << recipe.ingredients_[i][j] << " ";
                }
            }    
            o << std::endl;
        }

        //instructions
        o << std::endl << "Instructions:" << std::endl;
        for (int i = 0; i < instruction_size; i++) {
            o << recipe.instructions_[i] << std::endl;
        }
        o << std::endl;    
        return o;
    }
};
