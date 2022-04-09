#Project 3 Description:
In this project, you will be making a header-only library that defines a class that can hold recipes and a class that represents a (extremely) simple recipe app.
Descriptions of the only three files that should be submitted:
  - **recipe.h: Contain the declaration and definition of a class named Recipe. Can also contain other functions / classes if you find them useful. 
  - **app.h: Contain the declaration and definition of a class named RecipeApp. Can also contain other functions / classes if you find them useful. 
  - **utility.h: This file is never directly included by the unit tests, but you can put code needed to be included by the other files in this file if you would like.

Only the public member functions of Recipe and RecipeApp you are allowed to have are described here. Your solutions will likely have private attributes, as well as, additional functions and classes to support the described classes.

The test cases make use of raw string literals. The R”(…)” is how to make a raw  string literal. This is useful for using multiline strings in code. See: https://stackoverflow.com/questions/1135841/c-multiline-string-literal 

**class Recipe**
This class should have a constructor that takes a string (representing the name of a recipe) and a integer representing the number of servings this recipe will serve. In this project, all number of servings will be positive integers. Example: Recipe r("Microwave Popcorn", 3);

There should be a member function named AddIngredient that accepts a string with three parts: a (possibly fractional) value, a unit, and a name each separated by white space. For example: r.AddIngredient("1/2 cup unpopped popcorn")

The values can consist of whole numbers (i.e. 4), fractions (i.e. 3/4), mixed fractions (i.e. 3-4/5), or even improper fractions (i.e. 9/4). All values when written to an ostream must be in reduced-mixed form (3-9/2 should become 7-1/2).

The class should also have a member function named SetInstructions that accepts a (possibly multiline) string denoting the instructions to follow for the recipe. This string may have blank lines, leading whitespace, and/or trailing whitespace on each line. This whitespace should be removed when a Recipe is written to an ostream.

The class should support the operator<< to write to an ostream. Please see the test cases or below for examples of the specific formatting required.

The class should also support a function, named IngredientInOneServing, which accepts the name of a possible ingredient, and results a string denoting the value, unit, and name (each delimited by a space character) of the ingredient that a single serving of the recipe would require. Example, if Microwave Popcorn serves 3, and has as "1/2 cup unpopped popcorn" an ingredient, then a call like r.IngredientInOneServing("unpopped popcorn") would return "1/6 cup unpopped popcorn". If the recipe doesn't use that ingredient, throw a std::invalid_argument exception.

Lastly, the class should support a member function named ChangeServings that accepts a positive integer denoting the number of servings the values of the ingredients should be scaled to. This member function should mutate the Recipe to reflect the change.

Here is an example of using the Recipe class:

  Recipe r("Microwave Popcorn", 3);
  r.AddIngredient("1/2 cup unpopped popcorn");
  r.AddIngredient("1 teaspoon vegetable oil");
  r.AddIngredient("1/2 teaspoon salt");
  r.SetInstructions(
      R"***(In a cup or small bowl, mix together the unpopped popcorn and oil. 
  Pour the coated corn into a brown paper lunch sack, and sprinkle in the salt. 
    Fold the top of the bag over twice to seal in the ingredients. 

  Cook in the microwave at full power for 2 1/2 to 3 minutes, 
   or until you hear pauses of about 2 seconds between pops. 

  Carefully open the bag to avoid steam, and pour into a serving bowl. 
  From: https://www.allrecipes.com/recipe/87305/microwave-popcorn/
  )***");

  std::cout << r << std::endl;

  std::ostringstream oss;
  oss << r;
  std::string expected = R"***(Recipe for: Microwave Popcorn
Serves 3
Ingredients:
1/2 cup unpopped popcorn
1 teaspoon vegetable oil
1/2 teaspoon salt

Instructions:
In a cup or small bowl, mix together the unpopped popcorn and oil.
Pour the coated corn into a brown paper lunch sack, and sprinkle in the salt.
Fold the top of the bag over twice to seal in the ingredients.
Cook in the microwave at full power for 2 1/2 to 3 minutes,
or until you hear pauses of about 2 seconds between pops.
Carefully open the bag to avoid steam, and pour into a serving bowl.
From: https://www.allrecipes.com/recipe/87305/microwave-popcorn/

)***";

  std::cout << expected << std::endl;

  assert(oss.str() == expected);

  std::cout << r.IngredientInOneServing("unpopped popcorn") << std::endl;

  std::cout << "Changing servings to 6" << std::endl;
  r.ChangeServings(6);

  std::cout << r << std::endl;

**class RecipeApp:**

This class represents a simple recipe manager that can save recipes and items in a pantry. And can also scale recipes to consume nearly all of a particular ingredient a customer have have.

This class should have a default constructor.

This class should have a member function named AddRecipe that accepts a Recipe and saves it in the class.

This class should have a member function named AddIngredientToPantry that accepts a string denoting the value, unit, and name of an ingredient and saves it in the class.

This class should support the operator<< and write itself to an ostream with both the recipes and pantry contents ordered by name.

Lastly, this class should implement a member function named UseUpIngredient that accepts a string denoting the value, unit, and name of an ingredient. It should search the recipes (in order by name) and if the recipe uses that ingredient, it should return a copy of that recipe with the most amount of number of servings that the recipe can support with the indicated ingredient. If no recipe uses that ingredient, throw a std::invalid_argument exception.

Here is an example of using the RecipeApp class:

  RecipeApp ra;
  Recipe simple_pop("Simple Popcorn", 1);
  simple_pop.AddIngredient("1/4 cup unpopped popcorn");
  simple_pop.AddIngredient("1/4 teaspoon vegetable oil");
  simple_pop.AddIngredient("1/4 teaspoon salt");
  simple_pop.SetInstructions(R"***(Pop it!)***");

  Recipe apples("An Apple", 3);
  apples.AddIngredient("1-5/6 unit apple");
  apples.SetInstructions(R"***(Grab it!)***");

  ra.AddRecipe(simple_pop);
  ra.AddRecipe(apples);
  ra.AddIngredientToPantry("2 cup unpopped popcorn");
  ra.AddIngredientToPantry("4-7/8 unit apple");
  std::cout << ra << std::endl;

  Recipe r = ra.UseUpIngredient("10 unit apple");
  std::cout << "Using up apples" << std::endl;
  std::cout << r;

  std::cout << ra;

Manually Graded Components:

25 points on this project are set aside for manual grading.

Short Functions. Most functions should generally be less than 10 C++ statements long. No function in this assignment should be more than 20 statements long. We won’t be directly counting statements, but if you are writing excessively long functions that could have been simplified into smaller functions, you will be marked down.

No Duplicated Code. Code should be put into useful functions and called wherever needed, not essentially copy-pasted in multiple locations.

Informative Names. All variables and functions should have clear names describing their purpose.

Appropriate Type Modifiers. Whenever possible const and references should be used to avoid unnecessary object copying and to make it clear what each function needs from its arguments.

Conformance To The Style Guide. Ensure that your solution conforms to the white space rules, naming conventions, and other relevant parts of the style guide.

Appropriate use of access control (only the listed member functions above should be public, all else must be private).
