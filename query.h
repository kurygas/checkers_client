#pragma once
#include <QVariant>
#include <QString>
#include <QList>

enum class QueryId {
    QueryBegin = 0,
    StringBegin,
    Login,
    Register,
    Join,
    Create,
    ChangeNickname,
    ChangePassword,
    AcceptResult,
    Accept,
    Ok,
    NotExist,
    AlreadyExist,
    WrongPassword,
    RoomList,
    Public,
    Private,
    Accepted,
    Declined,
    Delete,
    Same
};

class Query {
public:
    explicit Query(QueryId queryId);
    explicit Query(const QByteArray& bytes);

    void PushInfo(const QString& info);
    void PushInfo(QueryId info);

    [[nodiscard]] QueryId GetId() const;
    [[nodiscard]] QueryId GetIdInfo(int index) const;
    [[nodiscard]] QString GetStringInfo(int index) const;
    [[nodiscard]] QByteArray ToBytes() const;
    [[nodiscard]] size_t Size() const;

    static QueryId Type(char symbol);

private:
    QueryId queryId_;
    QList<QVariant> queryData_;
};
