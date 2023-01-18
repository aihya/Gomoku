#include "minimax.hpp"
#include <bitset>

#define COORDS(result) (result.first)
#define SCORE(result) (result.second)
#define GET_BIT(bitset, index) (bitset[18 + index])

u_long reverse_bitset(u_long num)
{
    // This function should be used when we create new board.
    u_long rev;

    rev = 0;
    while (num > 0)
    {
        rev <<= 1;
        rev |= num & 1 ? 1 : 0;
        num >>= 1;
    }
    return rev;
}

t_superposition superpose(t_board &board)
{
    t_superposition sup;
    ulong num;

    for (t_board::iterator row = board.begin(); row != board.end(); row++)
    {
        num = (*row).first.to_ulong() | (*row).second.to_ulong();
        sup.push_back(std::bitset<19>{num});
    }
    return sup;
}

std::vector<t_coord> get_coords(t_board &board, int player)
{
    std::vector<t_coord> coords;
    t_superposition sup;

    sup = superpos(board);
    for (int r = 0; r < 19; r++)
    {
        for (int c = 0; c < 19; c++)
        {
            if (!sup[r].first[c])
            {
                // If one of the below conditions met, we move to the next position.
                if (((c + 1 < 19) && (sup[r][c] ^ sup[r][c+1])) || // Right
                    ((c - 1 > -1) && (sup[r][c] ^ sup[r][c-1])) || // Left
                    ((r + 1 < 19) && (sup[r][c] ^ sup[r+1][c])) || // Top
                    ((r - 1 > -1) && (sup[r][c] ^ sup[r-1][c])) || // Bottom
                    ((c + 1 < 19) && (r + 1 < 19) && (sup[r][c] ^ sup[r+1][c+1])) || // Bottom-Right
                    ((c + 1 < 19) && (r - 1 < 19) && (sup[r][c] ^ sup[r-1][c+1])) || // Top-Right
                    ((c - 1 < 19) && (r + 1 < 19) && (sup[r][c] ^ sup[r+1][c-1])) || // Bottom-Left
                    ((c - 1 < 19) && (r - 1 < 19) && (sup[r][c] ^ sup[r-1][c-1])))   // Top-Left
                    coords.push_back(t_coord{r, c});
            }
        }
    }
    return coords;
}


t_board update_board(t_board &board, t_coord &coord, int player)
{
    t_board new_board;

    new_board = board;
    if (player == 1)
        new_board[coord.first].first.set(coord.second, 1);
    else
        new_board[coord.forst].second.set(coord.second, 1);
    return new_board;
}


std::pair<t_coord, int> maximize(int depth, t_board &board, int &alpha, int &beta, int player)
{
    std::pair<std::pair<int, int>, int> result;
    int best_index;
    int best_score;

    children = get_possible_coords(board);
    best_score = INT32_MIN;
    best_index = 0;

    for (int i = 0; i < children.size(); i++)
    {
        result = minimax(depth - 1, update_board(board, children[i]), alpha, beta, false);
        alpha = std::max(alpha, SCORE(result));
        if (beta <= alpha)
            break ;
        best_index = i;
        best_score = std::max(SCORE(result), best_score);
    }
    result.first = children[best_index];
    result.second = best_score;
    return result;
}


std::pair<t_coord, int> minimize(int depth, t_board &board, int &alpha, int &beta, int player)
{
    std::pair<t_coord, int> result;
    int best_index;
    int best_score;

    children = get_possible_coords(board, player);
    best_score = INT32_MAX;
    best_index = 0;

    for (int i = 0; i < children.size(); i++)
    {
        result = minimax(depth - 1, update_board(board, children[i]), alpha, beta, true);
        beta = std::min(beta, SCORE(result));
        if (beta <= alpha)
            break ;
        best_index = i;
        best_score = std::min(SCORE(result), best_score);
    }

    result.first = children[best_index];
    result.second = best_score;
    return result;
}


std::pair<t_coord, int> minimax(int depth, t_board &board, int &alpha, int &beta, int is_max, int player)
{
    if (depth == 0)
        return static_evaluation(board);
    if (is_max)
        return maximize(depth, board, alpha, beta, player);
    return minimize(depth, board, alpha, beta, player);
}


int parse_settings(int argc, char **argv)
{
    
}


int main(int argc, char **argv)
{
    // Pipeline:
    // 1. if the first player:
    //      Enter the loop cycle directly
    //      Make an educated guess
    //      Output the result
    // 2. if the second player:
    //      Read the current state of the board
    //      Make an educated guess
    //      Output the result

    return (0);
}