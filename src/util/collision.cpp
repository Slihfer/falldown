#include "collision.h"

#include <array>
#include <algorithm>

#include "util/rectangle.h"
#include "util/vector.h"

Rectangle AssembleCollider(Vector2 position, Rectangle collider)
{
    return { position.x + collider.x, position.y + collider.y, collider.width, collider.height };
}

Vector2 GetFixedMobileUnstuckVector(Rectangle fixedCollider, Rectangle mobileCollider, Rectangle previousMobileCollider)
{
    //"signed distance of previous mobile left edge from fixed right edge"
    float sd_pml_fr = previousMobileCollider.x - GetRectangleRight(fixedCollider);
    float sd_pmb_ft = fixedCollider.y - GetRectangleBottom(previousMobileCollider);
    float sd_pmr_fl = fixedCollider.x - GetRectangleRight(previousMobileCollider);
    float sd_pmt_fb = previousMobileCollider.y - GetRectangleBottom(fixedCollider);

    float sd_ml_fr = mobileCollider.x - GetRectangleRight(fixedCollider);
    float sd_mb_ft = fixedCollider.y - GetRectangleBottom(mobileCollider);
    float sd_mr_fl = fixedCollider.x - GetRectangleRight(mobileCollider);
    float sd_mt_fb = mobileCollider.y - GetRectangleBottom(fixedCollider);

    std::array<float, 4> values =
    {
        sd_pml_fr >= 0 && sd_ml_fr < 0 ? sd_ml_fr - sd_pml_fr : -std::numeric_limits<float>::infinity(),
        sd_pmb_ft >= 0 && sd_mb_ft < 0 ? sd_mb_ft - sd_pmb_ft : -std::numeric_limits<float>::infinity(),
        sd_pmr_fl >= 0 && sd_mr_fl < 0 ? sd_mr_fl - sd_pmr_fl : -std::numeric_limits<float>::infinity(),
        sd_pmt_fb >= 0 && sd_mt_fb < 0 ? sd_mt_fb - sd_pmt_fb : -std::numeric_limits<float>::infinity()
    };

    int furthestIndex = std::distance(values.begin(), std::max_element(values.begin(), values.end()));

    if (values[furthestIndex] == -std::numeric_limits<float>::infinity())
    {
        values =
        {
            sd_ml_fr < 0 ? sd_ml_fr : -std::numeric_limits<float>::infinity(),
            sd_mb_ft < 0 ? sd_mb_ft : -std::numeric_limits<float>::infinity(),
            sd_mr_fl < 0 ? sd_mr_fl : -std::numeric_limits<float>::infinity(),
            sd_mt_fb < 0 ? sd_mt_fb : -std::numeric_limits<float>::infinity()
        };

        furthestIndex = std::distance(values.begin(), std::max_element(values.begin(), values.end()));
    }

    switch (furthestIndex)
    {
    case 0: return { -sd_ml_fr, 0.0f };
    case 1: return { 0.0f, sd_mb_ft };
    case 2: return { sd_mr_fl, 0.0f };
    case 3: return { 0.0f, -sd_mt_fb };
    }
}