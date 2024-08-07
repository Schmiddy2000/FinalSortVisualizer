//
// Created by Luca Schmitt on 07.08.24.
//

#include "Settings.h"

#include <memory>

class Application;

// ----- Static member definitions ----- \\

// Font sizes
// Static member definitions
int FontSize::Tiny = 10;
int FontSize::Small = 12;
int FontSize::Medium = 16;
int FontSize::Large = 24;
int FontSize::Huge = 36;

// Colorspace
sf::Color ColorSpace::buttonForeground;
sf::Color ColorSpace::buttonBackground;

sf::Color ColorSpace::textForeground;
sf::Color ColorSpace::textBackground;

sf::Color ColorSpace::screenBackground;


// Settings
std::shared_ptr<sw::Application> Settings::appPointer = nullptr;
std::pair<int, int> Settings::windowSize = std::pair(1080, 640);
// Define here and set value in the MainApplication constructor
bool Settings::darkMode;
u_int8_t Settings::frameRate = 24;
float Settings::sortingSpeed = 2.5;
// Define the static variable here and load it in the MainApplication constructor.
sf::Font Settings::font;
sf::Font Settings::boldFont;

// Fonts
std::string Fonts::RobotoLight = "/Users/lucas1/UnityProjects/ParticleTests1_URP/Library/PackageCache/com.unity."
                                 "searcher@4.9.2/Editor/Resources/FlatSkin/Font/Roboto-Light.ttf";
std::string Fonts::SourceCodeProLight = "/Users/lucas1/miniconda3/pkgs/font-ttf-source-code-pro-2.038-h77eed37_0/fonts"
                                        "/SourceCodePro-Light.ttf";

std::string Fonts::RobotoMedium = "/Users/lucas1/UnityProjects/ParticleTests1_URP/Library/PackageCache/com.unity."
                                  "searcher@4.9.2/Editor/Resources/FlatSkin/Font/Roboto-Medium.ttf";

std::string Fonts::DejaVuSansMono = "/Users/lucas1/CLionProjects/SortVisualizer/Fonts/DejaVuSansMono.ttf";
std::string Fonts::OpenSansRegular = "/Users/lucas1/PycharmProjects/Ursina_1/venv/lib/python3.10/site-packages/ursina/"
                                     "fonts/OpenSans-Regular.ttf";
std::string Fonts::PTSansNarrowRegular = "/Users/lucas1/Desktop/Xcode/_Own Projects/Challengers Conceptual Testing/"
                                         "Challengers Conceptual Testing/Dependencies/Fonts/PTSansNarrow-Regular.ttf";
std::string Fonts::RobotoRegular = "/Users/lucas1/UnityProjects/ParticleTests1_URP/Library/PackageCache/com.unity."
                                   "searcher@4.9.2/Editor/Resources/FlatSkin/Font/Roboto-Regular.ttf";
std::string Fonts::SFPro = "/Library/Fonts/SF-Pro.ttf";
std::string Fonts::SourceCodeProRegular = "/Users/lucas1/miniconda3/pkgs/font-ttf-source-code-pro-2.038-h77eed37_0/"
                                          "fonts/SourceCodePro-Regular.ttf";

std::string Fonts::SourceCodeProBold = "/Users/lucas1/miniconda3/pkgs/font-ttf-source-code-pro-2.038-h77eed37_0/fonts"
                                       "/SourceCodePro-Bold.ttf";
