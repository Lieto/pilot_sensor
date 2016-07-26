//
// Created by kuoppves on 24.7.2016.
//

#include <iomanip>
#include "DataCounter.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

using namespace rapidjson;
using namespace std;


DataCounter::DataCounter(int send_interval) : m_interval(send_interval) {
    m_last_sendtime = time_t(NULL);

}

DataCounter::~DataCounter() {

}

string DataCounter::asJSON(Visitor *visitor) {

    StringBuffer s;
    Writer<StringBuffer> writer(s);

    writer.StartObject();

    writer.String("unitGUID");
    writer.Int64(getUnitGUID());

    writer.String("ID");
    writer.Int64(visitor->m_ID);

    writer.String("firstObserved");
    writer.Int64(visitor->m_first_observed);

    writer.String("lastObserved");
    writer.Int64(visitor->m_last_observed);

    writer.String("age");
    writer.Double(visitor->getAge());

    writer.String("gender");
    writer.Double(visitor->getGender());

    writer.String("happiness");
    writer.Double(visitor->getHappiness());

    writer.String("surprised");
    writer.Double(visitor->getSurprised());

    writer.String("angry");
    writer.Double(visitor->getAngry());

    writer.String("disgusted");
    writer.Double(visitor->getDisgusted());

    writer.String("afraid");
    writer.Double(visitor->getAfraid());

    writer.String("sad");
    writer.Double(visitor->getSad());

    writer.String("mood");
    writer.Double(visitor->getMood());

    writer.String("attentionSpan");
    writer.Double(visitor->getAttentionSpanAvg());

    writer.String("colors");
    writer.StartArray();
    for (auto const& rgb : visitor->m_colors) {
        writer.Uint(rgb);
    }

    writer.EndArray();

    writer.String("sampleCount");
    writer.Int(visitor->m_sample_count);

    writer.EndObject();

    return s.GetString();
}