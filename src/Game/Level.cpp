//
// Created by Dmitry on 04.08.2022.
//

#include "Level.h"


Level::Level() {
    ChessFraction side;
    std::string name;
    double y;
    double x = 0;
    for (int i = 0; i < 8; ++i) {
        if (i == 0)name = "a";
        if (i == 1)name = "b";
        if (i == 2)name = "c";
        if (i == 3)name = "d";
        if (i == 4)name = "e";
        if (i == 5)name = "f";
        if (i == 6)name = "g";
        if (i == 7)name = "h";
        for (int j = 0; j < 8; ++j) {
            std::string nowName = name + std::to_string(j + 1);
            y = 100.0f * j;
            if (i % 2 == 0) {
                side = ChessFraction::WHITE;
                if (j % 2 == 0) side = ChessFraction::BLACK;
            } else {
                side = ChessFraction::BLACK;
                if (j % 2 == 0) side = ChessFraction::WHITE;
            }
            mLvl.emplace(nowName, SquareNode(glm::vec2(x, y), glm::vec2(100.0f, 100.0f), side));
        }
        x += 100;
    }

    for (int i = 0; i < 8; ++i) {
        if (i == 0)name = "a";
        if (i == 1)name = "b";
        if (i == 2)name = "c";
        if (i == 3)name = "d";
        if (i == 4)name = "e";
        if (i == 5)name = "f";
        if (i == 6)name = "g";
        if (i == 7)name = "h";
        std::string nowName = name + std::to_string(2);
        auto node = mLvl.find(nowName);
        node->second.setFigure(Figure::FigureType::PAWN, 0);
    }
    auto a1 = mLvl.find("a1");
    a1->second.setFigure(Figure::FigureType::ROOK, 0);
    auto b1 = mLvl.find("b1");
    b1->second.setFigure(Figure::FigureType::BISHOP, 0);
    auto c1 = mLvl.find("c1");
    c1->second.setFigure(Figure::FigureType::KNIGHT, 0);
    auto d1 = mLvl.find("d1");
    d1->second.setFigure(Figure::FigureType::QUEEN, 0);
    auto e1 = mLvl.find("e1");
    e1->second.setFigure(Figure::FigureType::KING, 0);
    auto f1 = mLvl.find("f1");
    f1->second.setFigure(Figure::FigureType::KNIGHT, 0);
    auto g1 = mLvl.find("g1");
    g1->second.setFigure(Figure::FigureType::BISHOP, 0);
    auto h1 = mLvl.find("h1");
    h1->second.setFigure(Figure::FigureType::ROOK, 0);


    for (int i = 0; i < 8; ++i) {
        if (i == 0)name = "a";
        if (i == 1)name = "b";
        if (i == 2)name = "c";
        if (i == 3)name = "d";
        if (i == 4)name = "e";
        if (i == 5)name = "f";
        if (i == 6)name = "g";
        if (i == 7)name = "h";
        std::string nowName = name + std::to_string(7);
        auto node = mLvl.find(nowName);
        node->second.setFigure(Figure::FigureType::PAWN, 1);
    }
    auto a8 = mLvl.find("a8");
    a8->second.setFigure(Figure::FigureType::ROOK, 1);
    auto b8 = mLvl.find("b8");
    b8->second.setFigure(Figure::FigureType::BISHOP, 1);
    auto c8 = mLvl.find("c8");
    c8->second.setFigure(Figure::FigureType::KNIGHT, 1);
    auto d8 = mLvl.find("d8");
    d8->second.setFigure(Figure::FigureType::QUEEN, 1);
    auto e8 = mLvl.find("e8");
    e8->second.setFigure(Figure::FigureType::KING, 1);
    auto f8 = mLvl.find("f8");
    f8->second.setFigure(Figure::FigureType::KNIGHT, 1);
    auto g8 = mLvl.find("g8");
    g8->second.setFigure(Figure::FigureType::BISHOP, 1);
    auto h8 = mLvl.find("h8");
    h8->second.setFigure(Figure::FigureType::ROOK, 1);
}

Level::~Level() {
    mLvl.clear();
}

void Level::render() {
    for (auto &x: mLvl) {
        x.second.render();
    }
}

void Level::move(SquareNode &source, SquareNode &dist) {
    dist.swapFigure(source.mFigure);
}

void Level::move(const std::string &source, const std::string &dist) {
    auto src = mLvl.find(source);
    auto dst = mLvl.find(dist);
    move(src->second, dst->second);
}

