#ifndef PLAYER_H
#define PLAYER_H
#include "UnitType.h"
#include "cards.h"
#include <QObject>

namespace basedata
{
class EXPORT_BASEDATA_ABI Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    explicit Player(QString name ,QObject *parent = nullptr);
    void setName(QString name);
    QString getName();
    void setRole(Role role);
    Role getRole();
    void setSex(Sex sex);
    Sex getSex();
    void direction(PlayerDir dir);
    PlayerDir getDirection();
    void setType(PlayerType type);
    PlayerType getType();
    void setScore(int score);
    int getScore();
    void setWin(bool win);
    bool getWin();
    void setPrePlayer(Player* player);
    Player* getPrePlayer();
    void setNextPlayer(Player* player);
    Player* getNextPlayer();
    void setGradPoint(int point);
    int getPoint();
    void storeDispatchcard(Card& card);
    void storeDispatchcards(Cards& cards);
    Cards getCards();
    void clearCards();
    void playHand(Cards& cards);
    void setPandInfo(Player* player,Cards cards);
    Player* getPandPlayer();
    Cards getPandCards();

    virtual void preparecallLord();
    virtual void preparePlayHand();
signals:
    //通知已经下注了
    void notifyGrabLordBet(Player* player,int bet);

protected:
    QString m_name;
    Role m_role;
    Sex m_sex;
    PlayerDir m_dir;
    PlayerType m_type;
    int m_score;
    bool m_isWin;
    Player* m_PrePlayer;
    Player* m_NextPlayer;
    int m_gradPoint;
    Cards m_cards;//玩家手中的牌
    Cards m_PendCards;//本轮打出的牌
    Player* m_Pendplayer;
};

} //end of namespace basedata

#endif // PLAYER_H
