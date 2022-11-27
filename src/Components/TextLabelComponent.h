#ifndef CDAACAEC_68E4_48FC_B11B_32AFBC01093C
#define CDAACAEC_68E4_48FC_B11B_32AFBC01093C

#include <glm/glm.hpp>
#include <string>
#include <SDL2/SDL.h>

struct TextLabelComponent {
    glm::vec2 position;
    std::string text;
    std::string assetId;
    SDL_Color color;
    bool isFixed;

    TextLabelComponent(glm::vec2 position = glm::vec2(0), std::string text = "", std::string assetId = "",
                       const SDL_Color& color = {0, 0, 0}, bool isFixed = true)
        : position(position), text(text), assetId(assetId), color(color), isFixed(isFixed) {}
};

#endif /* CDAACAEC_68E4_48FC_B11B_32AFBC01093C */
