#include <iostream>
#include <cstdlib>

using namespace std;

enum en_pass_or_fail { pass, fail };

enum en_question_level { easy = 1, med, hard, mix_level };

enum en_operation_type { add = 1, sub, mul, division, mix_operations };

struct st_question_numbers
{
    float num1, num2;
};

struct st_question_info
{
    en_question_level question_level;
    en_operation_type operation_type;
    st_question_numbers question_numbers;
    float correct_answer, user_answer;
    short no_of_right_answers, no_of_wrong_answers;
};

int random_number(int min, int max)
{
    int random_number = rand() % (max - min + 1) + min;
    return random_number;
}

short read_questions_number()
{
    short number_of_questions;
    do
    {
        cout << "How many questions do you want to answer? ";
        cin >> number_of_questions;
    } while (number_of_questions <= 0);
    return number_of_questions;
}

en_question_level read_question_level()
{
    short question_level;
    do
    {
        cout << "Enter question level [1] Easy, [2] Med, [3] Hard, [4] Mix: ";
        cin >> question_level;
    } while (question_level < 1 || question_level > 4);
    return en_question_level(question_level);
}

en_operation_type read_operation_type()
{
    short operation_type;
    do
    {
        cout << "Enter operation type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix: ";
        cin >> operation_type;
    } while (operation_type < 1 || operation_type > 5);
    return en_operation_type(operation_type);
}

char convert_operation_type(en_operation_type operation_type)
{
    if (operation_type == add)
        return '+';
    else if (operation_type == sub)
        return '-';
    else if (operation_type == mul)
        return '*';
    return '/';
}

float get_correct_answer(st_question_info question_info)
{
    if (question_info.operation_type == add)
        question_info.correct_answer = question_info.question_numbers.num1 + question_info.question_numbers.num2;
    else if (question_info.operation_type == sub)
        question_info.correct_answer = question_info.question_numbers.num1 - question_info.question_numbers.num2;
    else if (question_info.operation_type == mul)
        question_info.correct_answer = question_info.question_numbers.num1 * question_info.question_numbers.num2;
    else
        question_info.correct_answer = question_info.question_numbers.num1 / question_info.question_numbers.num2;
    return question_info.correct_answer;
}

bool validate_answer(st_question_info question_info)
{
    if (question_info.user_answer == question_info.correct_answer)
        return true;
    return false;
}

void fill_question_numbers(st_question_info& question_info)
{
    if (question_info.question_level == easy)
    {
        question_info.question_numbers.num1 = random_number(1, 10);
        question_info.question_numbers.num2 = random_number(1, 10);
    }
    else if (question_info.question_level == med)
    {
        question_info.question_numbers.num1 = random_number(11, 100);
        question_info.question_numbers.num2 = random_number(11, 100);
    }
    else if (question_info.question_level == hard)
    {
        question_info.question_numbers.num1 = random_number(101, 1000);
        question_info.question_numbers.num2 = random_number(101, 1000);
    }
}

void print_question(st_question_info& question_info)
{
    fill_question_numbers(question_info);
    question_info.correct_answer = get_correct_answer(question_info);
    cout << question_info.question_numbers.num1 << endl;
    cout << question_info.question_numbers.num2 << "  " << convert_operation_type(question_info.operation_type);
    cout << "\n______________\n";
    cin >> question_info.user_answer;
    if (validate_answer(question_info))
    {
        cout << "Right answer :-)";
        question_info.no_of_right_answers++;
    }
    else
    {
        cout << "Wrong answer :-(";
        cout << "\nThe right answer is: " << question_info.correct_answer;
        question_info.no_of_wrong_answers++;
    }
}

en_pass_or_fail check_pass_or_fail(st_question_info question_info)
{
    if (question_info.no_of_right_answers >= question_info.no_of_wrong_answers)
        return pass;
    return fail;
}

void print_pass_or_fail(en_pass_or_fail pass_or_fail)
{
    cout << "\n____________________________________\n";
    cout << "       Final Result is ";
    if (pass_or_fail == pass)
        cout << "Pass :-)";
    else cout << "Fail :-(";
    cout << "\n____________________________________\n";
}

void print_question_level(st_question_info question_info)
{
    if (question_info.question_level == easy)
        cout << "Easy";
    else if (question_info.question_level == med)
        cout << "Med";
    else if (question_info.question_level == hard)
        cout << "Hard";
    else cout << "Mix";
}

void print_operation_type(st_question_info question_info)
{
    if (question_info.operation_type == add)
        cout << "Add";
    else if
        (question_info.operation_type == sub)
        cout << "Sub";
    else if
        (question_info.operation_type == mul)
        cout << "Mul";
    else if
        (question_info.operation_type == division)
        cout << "Div";
    else cout << "Mix";
}

void print_game_results(short no_of_questions, st_question_info question_info)
{
    cout << "Number Of Questions: " << no_of_questions;
    cout << "\nQuestions Level: ";
    print_question_level(question_info);
    cout << "\nOperation Type: ";
    print_operation_type(question_info);
    cout << "\nNumber Of Right Answers: " << question_info.no_of_right_answers;
    cout << "\nNumber Of Wrong Answers: " << question_info.no_of_wrong_answers;
    cout << "\n____________________________________\n";
}

void game()
{
    st_question_info question_info;
    short no_of_questions = read_questions_number();
    question_info.question_level = read_question_level();
    question_info.operation_type = read_operation_type();
    en_question_level question_level_temp;
    en_operation_type operation_type_temp;
    question_level_temp = question_info.question_level;
    operation_type_temp = question_info.operation_type;
    question_info.no_of_right_answers = 0;
    question_info.no_of_wrong_answers = 0;
    for (short i = 1; i <= no_of_questions; i++)
    {
        cout << "\nQuestion [" << i << "/" << no_of_questions << "]\n";
        if (question_level_temp == mix_level)
            question_info.question_level = en_question_level(random_number(1, 3));
        if (operation_type_temp == mix_operations)
            question_info.operation_type = en_operation_type(random_number(1, 4));
        print_question(question_info);
    }
    question_info.question_level = question_level_temp;
    question_info.operation_type = operation_type_temp;
    print_pass_or_fail(check_pass_or_fail(question_info));
    print_game_results(no_of_questions, question_info);
}

void start_game()
{
    char play_again;
    do
    {
        game();
        do
        {
            cout << "\nDo you want to play again? (y/n)";
            cin >> play_again;
        } while (play_again != 'y' && play_again != 'Y' && play_again != 'n' && play_again != 'N');
    } while (play_again == 'y' || play_again == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));
    start_game();
}