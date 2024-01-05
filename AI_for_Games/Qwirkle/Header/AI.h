#ifndef AI_H
#define AI_H

#include "TileMap.h"

class AI {
public:
    AI() = default;

    sf::Vector2i placeChess(const std::vector<std::vector<Tile>>& t_tiles)
    {
    }

    int evaluateMove(const std::vector<std::vector<Tile>>& board, int x, int y, const Tile& tile) {
        int score = 0;
        score += calculateImmediateScore();

        int minOpponentScore = INT_MAX;
        // Evaluate potential opponent responses
        /*
        for (const auto& oppMove : getAllPossibleOpponentMoves()) {
            int opponentScore = calculateImmediateScore(board, oppMove.x, oppMove.y, oppMove.tile);
            minOpponentScore = std::min(minOpponentScore, opponentScore);
        }
        */

        score -= minOpponentScore;

        return score;
    }

    int calculateImmediateScore() {
        return ;
    }

    void getAllPossibleOpponentMoves() {
        return ;
    }
};

#endif