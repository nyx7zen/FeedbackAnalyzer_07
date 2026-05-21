#include "UIComponents.h"

#include "Constants.h"

const std::vector<std::string>& UIComponents::getCategories() {
    static const std::vector<std::string> categories = {
        u8"배송",
        u8"품질",
        u8"가격",
        u8"서비스",
        u8"사용성",
    };
    return categories;
}
