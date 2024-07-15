#include "query.h"

QueryId Query::Type(char symbol) {
    return static_cast<QueryId>(static_cast<uint8_t>(symbol));
}

Query::Query(QueryId queryId)
: queryId_(queryId) {}

Query::Query(const QByteArray& bytes)
: queryId_(Type(bytes.front())) {
    for (int i = 1; i < bytes.size(); ++i) {
        if (Type(bytes[i]) == QueryId::StringBegin) {
            auto stringSize = static_cast<uint8_t>(bytes[i + 1]);
            queryData_.push_back(QString(bytes.sliced(i + 2, stringSize)));
            i += stringSize + 1;
        }
        else {
            queryData_.emplace_back(static_cast<uint8_t>(bytes[i]));
        }
    }
}

void Query::PushInfo(QueryId info) {
    queryData_.emplace_back(static_cast<uint8_t>(info));
}

void Query::PushInfo(const QString& info) {
    queryData_.emplace_back(info);
}

QueryId Query::GetId() const {
    return queryId_;
}

QByteArray Query::ToBytes() const {
    QByteArray result(1, static_cast<char>(QueryId::QueryBegin));
    result.push_back(static_cast<char>(queryId_));

    for (const auto& info : queryData_) {
        if (info.canConvert<int>()) {
            result.push_back(static_cast<char>(info.toInt()));
        }
        else {
            auto str = info.toString();
            result.push_back(static_cast<char>(QueryId::StringBegin));
            result.push_back(static_cast<char>(str.size()));
            result.push_back(str.toUtf8());
        }
    }

    return result;
}

QString Query::GetStringInfo(int index) const {
    return queryData_[index].toString();
}

QueryId Query::GetIdInfo(int index) const {
    return static_cast<QueryId>(queryData_[index].toUInt());
}

size_t Query::Size() const {
    return queryData_.size();
}
