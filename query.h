#pragma once
#include <QString>
#include <QList>
#include <variant>

enum class QueryId {
    Query = 0,
    String,
    Int,
    Login,
    Register,
    ChangeNickname,
    ChangePassword,
    FindGame,
    WrongPassword,
    NotExist,
    AlreadyExist,
    Ok,
    EnemyDisconnected,
    StartGame,
    CancelSearching
};

class Query {
public:
    explicit Query(QueryId queryId);
    explicit Query(const QByteArray& bytes);

    void PushData(const std::variant<QString, uint, QueryId>& data);
    QByteArray ToBytes() const;
    size_t Size() const;
    QueryId GetId() const;

    static uint8_t ToNum(char symbol);
    static QueryId ToType(char symbol);

    template<typename T>
    static char ToChar(T&& data) {
        return static_cast<char>(data);
    }

    template<typename T>
    const T& GetData(size_t index) const {
        return std::get<T>(queryData_[index]);
    }


private:
    QueryId queryId_;
    QList<std::variant<QString, uint, QueryId>> queryData_;
};
