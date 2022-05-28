#include "svg.h"
#include <iostream>
#include <vector>
#include <math.h>


void //������� ������ ��������� � ��������� SVG
svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end()
{
    cout << "</svg>\n";
}

void
svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "' >" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";

}

void
show_histogram_svg(const vector<size_t>& bins, const vector<size_t>& proc)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto PROCENT = 50;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    const auto MAX_BIN_WIDTH = IMAGE_WIDTH - TEXT_WIDTH - PROCENT;

    size_t max_bins_width = bins[0];
    for (size_t bin : bins)
    {
        if (bin > max_bins_width)
        {
            max_bins_width = bin;
        }
    }

    max_bins_width = max_bins_width * BLOCK_WIDTH;

    double top = 0;
    for (size_t i = 0; i < bins.size(); i++)
    {
        double bin_width = BLOCK_WIDTH * bins[i];
        if (max_bins_width >= MAX_BIN_WIDTH)
        {
            bin_width = MAX_BIN_WIDTH * (bin_width / max_bins_width) - 1;
        }

        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "black", "blue");
        svg_text (MAX_BIN_WIDTH, top + TEXT_BASELINE, to_string(proc[i]) + '%');
        top += BIN_HEIGHT;

    }
    svg_end();
}
