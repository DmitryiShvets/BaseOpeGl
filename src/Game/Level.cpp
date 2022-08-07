//
// Created by Dmitry on 04.08.2022.
//

#include "Level.h"
#include "../Core/EventManager.h"

#include <thread>


Level::Level(int playerColor) {
    ChessFraction side;
    std::string name;
    double y;
    double x = 50;

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
            std::string nowName;
            if (playerColor == 0) nowName = name + std::to_string(j + 1);
            if (playerColor == 1) nowName = name + std::to_string(8 - j);
            y = 50.0f + (100.0f * j);
            if (i % 2 == 0) {
                side = ChessFraction::WHITE;
                if (j % 2 == 0) side = ChessFraction::BLACK;
            } else {
                side = ChessFraction::BLACK;
                if (j % 2 == 0) side = ChessFraction::WHITE;
            }
            mLvl.emplace(nowName, SquareNode(nowName, glm::vec2(x, y), side));

        }
        x += 100;
    }

    int suffix;
    int color;
    int index;
    for (int j = 2; j < 4; ++j) {

        if (j == 2) {
            suffix = 1;
            index = 2;
            color = 0;
        }
        if (j == 3) {
            suffix = 8;
            index = 7;
            color = 1;
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
            std::string nowName = name + std::to_string(index);
            auto node = mLvl.find(nowName);
            node->second.setFigure(Figure::FigureType::PAWN, color);
        }

        auto a1 = mLvl.find("a" + std::to_string(suffix));
        a1->second.setFigure(Figure::FigureType::ROOK, color);
        auto b1 = mLvl.find("b" + std::to_string(suffix));
        b1->second.setFigure(Figure::FigureType::KNIGHT, color);
        auto c1 = mLvl.find("c" + std::to_string(suffix));
        c1->second.setFigure(Figure::FigureType::BISHOP, color);
        auto d1 = mLvl.find("d" + std::to_string(suffix));
        d1->second.setFigure(Figure::FigureType::QUEEN, color);
        auto e1 = mLvl.find("e" + std::to_string(suffix));
        e1->second.setFigure(Figure::FigureType::KING, color);
        auto f1 = mLvl.find("f" + std::to_string(suffix));
        f1->second.setFigure(Figure::FigureType::BISHOP, color);
        auto g1 = mLvl.find("g" + std::to_string(suffix));
        g1->second.setFigure(Figure::FigureType::KNIGHT, color);
        auto h1 = mLvl.find("h" + std::to_string(suffix));
        h1->second.setFigure(Figure::FigureType::ROOK, color);
    }

    int xPos = 50;
    int yPos = 50;
    glm::vec3 background;
    for (int i = 0; i < 8; ++i) {
        if (i == 0)name = "a";
        if (i == 1)name = "b";
        if (i == 2)name = "c";
        if (i == 3)name = "d";
        if (i == 4)name = "e";
        if (i == 5)name = "f";
        if (i == 6)name = "g";
        if (i == 7)name = "h";

        if (i % 2 == 0) {
            background = glm::vec3(0.79f, 0.71f, 0.51f);

        } else {
            background = glm::vec3(0.48f, 0.54f, 0.20f);

        }

        mLabels.emplace_back(glm::vec2(xPos, 20), glm::vec2(100, 30), background, std::wstring(name.begin(), name.end()));
        mLabels.emplace_back(glm::vec2(xPos, 850), glm::vec2(100, 30), background, std::wstring(name.begin(), name.end()));
        int n;
        if (playerColor == 0)n = i + 1;
        if (playerColor == 1)n = 8 - i;
        mLabels.emplace_back(glm::vec2(20, yPos), glm::vec2(30, 100), background, std::to_wstring(n));
        mLabels.emplace_back(glm::vec2(850, yPos), glm::vec2(30, 100), background, std::to_wstring(n));

        xPos += 100;
        yPos += 100;
    }
    EventManager::getInstance().subscribe(Event::EventType::NODE_SELECTED_EVENT, this);
    EventManager::getInstance().subscribe(Event::EventType::MOVE_FIGURE_EVENT, this);

    if (playerColor == 0) greko.init(WHITE);
    if (playerColor == 1) greko.init(BLACK);


}

Level::~Level() {
    mLvl.clear();
    EventManager::getInstance().unsubscribe(Event::EventType::NODE_SELECTED_EVENT, this);
    EventManager::getInstance().unsubscribe(Event::EventType::MOVE_FIGURE_EVENT, this);
}

void Level::render() {
    for (auto &x: mLvl) {
        x.second.render();
    }
    for (auto &x: mLabels) {
        x.render();
    }

}

void Level::move(SquareNode &source, SquareNode &dist) {
    dist.swapFigure(source.mFigure);
    source.deleteFigure();

}

void Level::move(const std::string &source, const std::string &dist) {
    auto src = mLvl.find(source);
    auto dst = mLvl.find(dist);
    move(src->second, dst->second);
    if (source == "e8" && dist == "c8")move("a8", "d8");
    if (source == "e8" && dist == "g8")move("h8", "f8");
    if (source == "e1" && dist == "c1")move("a1", "d1");
    if (source == "e1" && dist == "g1")move("h1", "f1");
}

void Level::update(Event *e) {
    if (e->getType() == Event::EventType::NODE_SELECTED_EVENT) {
        auto *event = dynamic_cast<NodeSelectedEvent * >(e);
        if (!mCurrentSelectedNode.empty() && mCurrentSelectedNode != event->nodeName) {
            if (mLvl.find(mCurrentSelectedNode)->second.mFigure) {

                if (greko.MakeMovePlayer(mCurrentSelectedNode + event->nodeName)) {
                    move(mCurrentSelectedNode, event->nodeName);
                    //  std::future<std::string> task = std::async(std::launch::async, &Level::threadTask, this, [](std::string&, std::string&) {});
                    std::thread task(&Level::threadTask, this);

                    task.detach();
                    //auto mv = greko.MakeMoveEngine();
//                    auto mv = task.get();
//                    move(mv.substr(0, 2), mv.substr(2, 2));
//                    if (mv == "e8c8")move("a8", "d8");
                }

            }
            NodeUnselectedEvent ev(event->nodeName);
            EventManager::eventRoute(&ev);
            mCurrentSelectedNode = event->nodeName;

        }
        if (mLvl.find(event->nodeName)->second.mFigure && mCurrentSelectedNode != event->nodeName) {
            mCurrentSelectedNode = event->nodeName;

        } else {
            NodeUnselectedEvent ev(event->nodeName);
            EventManager::eventRoute(&ev);
            mCurrentSelectedNode.clear();
        }
    }
    if (e->getType() == Event::EventType::MOVE_FIGURE_EVENT) {
        auto *event = dynamic_cast<MoveFigureEvent * >(e);
        if (mLvl.find(event->srcNodeName)->second.mFigure) move(event->srcNodeName, event->distNodeName);
    }
}

void Level::threadTask() {
    auto mv = greko.MakeMoveEngine();

    move(mv.substr(0, 2), mv.substr(2, 2));
    string result, comment;
    if (Search::IsGameOver(greko.g_pos, result, comment)) {

        GameEndEvent e(result, comment);
        EventManager::eventRoute(&e);
    }
}

