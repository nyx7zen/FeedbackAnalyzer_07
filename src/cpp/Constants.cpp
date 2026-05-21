#include "Constants.h"

#include <utility>

namespace {
std::vector<std::string> makeKeywords(std::initializer_list<const char*> values) {
    std::vector<std::string> keywords;
    keywords.reserve(values.size());
    for (const char* value : values) {
        keywords.emplace_back(value);
    }
    return keywords;
}
}

std::map<std::string, std::vector<std::string>> Constants::SENTIMENT_KEYWORDS;
std::map<std::string, std::map<std::string, std::vector<std::string>>> Constants::CATEGORY_KEYWORDS;

void Constants::init() {
    SENTIMENT_KEYWORDS.clear();
    CATEGORY_KEYWORDS.clear();

    SENTIMENT_KEYWORDS[kSentimentPositive] = makeKeywords({
        u8"좋아요", u8"만족", u8"감사", u8"친절", u8"추천", u8"최고",
        u8"빠름", u8"정확", u8"편리", u8"훌륭", u8"좋습니다", u8"좋네요"
    });

    SENTIMENT_KEYWORDS[kSentimentNegative] = makeKeywords({
        u8"별로", u8"실망", u8"불만", u8"늦음", u8"문제", u8"불편",
        u8"최악", u8"나쁨", u8"아쉬움", u8"환불", u8"지연", u8"불친절"
    });

    CATEGORY_KEYWORDS[u8"배송"]["main"] = makeKeywords({
        u8"배송", u8"택배", u8"도착", u8"출고", u8"지연"
    });
    CATEGORY_KEYWORDS[u8"배송"]["speed"] = makeKeywords({
        u8"빠름", u8"지연", u8"늦음", u8"신속"
    });
    CATEGORY_KEYWORDS[u8"배송"]["status"] = makeKeywords({
        u8"추적", u8"도착", u8"출고"
    });

    CATEGORY_KEYWORDS[u8"품질"]["main"] = makeKeywords({
        u8"품질", u8"제품", u8"하자", u8"불량", u8"내구성"
    });
    CATEGORY_KEYWORDS[u8"품질"]["condition"] = makeKeywords({
        u8"불량", u8"하자", u8"스크래치", u8"파손"
    });
    CATEGORY_KEYWORDS[u8"품질"]["durability"] = makeKeywords({
        u8"튼튼", u8"내구성", u8"견고"
    });

    CATEGORY_KEYWORDS[u8"가격"]["main"] = makeKeywords({
        u8"가격", u8"비용", u8"가성비", u8"할인", u8"비쌈"
    });
    CATEGORY_KEYWORDS[u8"가격"]["amount"] = makeKeywords({
        u8"가격", u8"비용", u8"비쌈", u8"저렴"
    });
    CATEGORY_KEYWORDS[u8"가격"]["value"] = makeKeywords({
        u8"가성비", u8"할인", u8"혜택"
    });

    CATEGORY_KEYWORDS[u8"서비스"]["main"] = makeKeywords({
        u8"서비스", u8"상담", u8"응대", u8"문의", u8"친절"
    });
    CATEGORY_KEYWORDS[u8"서비스"]["support"] = makeKeywords({
        u8"상담", u8"응대", u8"문의", u8"안내"
    });
    CATEGORY_KEYWORDS[u8"서비스"]["attitude"] = makeKeywords({
        u8"친절", u8"불친절"
    });

    CATEGORY_KEYWORDS[u8"사용성"]["main"] = makeKeywords({
        u8"사용", u8"설치", u8"설명", u8"인터페이스", u8"편리"
    });
    CATEGORY_KEYWORDS[u8"사용성"]["ease"] = makeKeywords({
        u8"편리", u8"간단", u8"직관", u8"어려움"
    });
    CATEGORY_KEYWORDS[u8"사용성"]["guide"] = makeKeywords({
        u8"설명", u8"가이드", u8"설치"
    });
}
