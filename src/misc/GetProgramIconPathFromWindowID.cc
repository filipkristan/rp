#include "GetProgramIconPathFromWindowID.hh"
#include "ExportCommandOutputToArray.hh"
#include <string>
#include <fstream>

std::string getProgramIconPathFromWindowID(const std::string &id) {
    std::string outpath = "/tmp/chud.pam";
    std::string get = R"(xprop -id )" + id + " -notype 32c _NET_WM_ICON > " + outpath;
    std::string convert =
            R"(perl -0777 -ne '@d=/\d+/g; $i=0; while($i<@d){ $w=$d[$i]; $h=$d[$i+1]; last if !$w; $c=$w*$h; $p="P7\nWIDTH $w\nHEIGHT $h\nDEPTH 4\nMAXVAL 255\nTUPLTYPE RGB_ALPHA\nENDHDR\n"; $b=""; for($j=0;$j<$c;$j++){ $v=$d[$i+2+$j]; $b.=pack("CCCC", ($v>>16)&0xFF, ($v>>8)&0xFF, $v&0xFF, ($v>>24)&0xFF); } open(F, "|-", "convert", "pam:-" ,")"
            R"(/tmp/)" + id + R"(_${w}x${h}.png"); print F $p.$b; close(F); $i+=2+$c; }' )" + outpath;

    std::vector<std::string> out1 = runCommandAndReturnEachLineAsEntryInArray(get.c_str());
    std::vector<std::string> out2 = runCommandAndReturnEachLineAsEntryInArray(convert.c_str());

    // Set values and check if files exist, use a placeholder if no icon exists for a program
    std::string imagelocation = "/tmp/" + id + "_32x32.png";
    std::string imagelocation64 = "/tmp/" + id + "_64x64.png";
    std::string imagelocation128 = "/tmp/" + id + "_128x128.png";

    std::ifstream fin(imagelocation);
    std::ifstream fin64(imagelocation);
    std::ifstream fin128(imagelocation);

    // Check if a 32x32 image was generated
    // NOTE: Should add a mechanism for when no image was generated or a image of a higher/lover resolution was made
    if (fin) {
        // std::cout << "Png path: " << imagelocation << std::endl;
    } else {
        // std::cerr << "Unable to open " << imagelocation << std::endl;
        if (fin64) {
            // imagelocation = imagelocation64;
        } else {
            //  std::cerr << "Unable to open " << imagelocation64 << std::endl;
            if (fin128) {
                imagelocation = imagelocation128;
            }
            //  std::cerr << "Unable to open " << imagelocation128 << std::endl;
        }

        // std::cout << "Failed to find a icon!" << std::endl;
        //std::cout << "Try to convert file to 32x32!" << std::endl;
        imagelocation = "../res/favicon.png"; // set fallback image
    }

    return imagelocation;
}
