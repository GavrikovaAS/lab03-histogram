#include <iostream>
#include <vector>
#include <string>


using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1 - 1;



vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

void find_minmax(const vector<double>& numbers, double& min, double& max);

vector <size_t> procent (size_t number_count, const vector <size_t> bins);

void find_minmax(const vector<double>& numbers, double& min, double& max)
{
    if (numbers.size() == 0)
        return;

    else
    {
        min = numbers[0];
        max = numbers[0];
        for (double number : numbers)
        {
            if (number < min)
            {
                min = number;
            }
            if (number > max)
            {
                max = number;
            }
        }
    }
}

// SVG
void svg_begin(double width, double height);

void svg_text (double left, double baseline, string text);

void svg_rect (double x, double y, double width, double height, string stroke = "black", string fill = "black");

void svg_end();

void show_histogram_svg(const vector<size_t>& bins, const vector<size_t>& proc);


void //функции вывода заголовка и окончания SVG
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

//end

vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count)
{
    vector<size_t> bins(bin_count, 0);

    double min, max;
    find_minmax(numbers, min, max);

    double bin_size = (max - min) / bin_count;

    for (double number : numbers)
    {
        bool found = false;
        for (size_t j = 0; j < (bin_count - 1) && (!found); j++)
        {
            auto lo = min + bin_size * j;
            auto hi = min + bin_size * (j + 1);

            if ((lo <= number) && (number < hi))
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
        {
            bins[bin_count - 1]++;
        }
    }
    return bins;
}

void show_histogram_text(const vector<size_t>& bins)
{
    size_t max_bins = bins[0];
    for (size_t bin : bins)
    {
        if (bin > max_bins)
        {
            max_bins = bin;
        }
    }

    for (size_t bin : bins)
    {
        double height = bin;

        if (max_bins > MAX_ASTERISK)
        {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_bins);
        }

        if (bin < 100)
        {
            cout << ' ';
        }

        if (bin < 10)
        {
            cout << ' ';
        }

        cout << bin << "|";

        for (size_t i = 0; i < height; i++)
        {
            cout << "*";
        }
        cout << "\n";
    }
}



int main()
{
    //Ввод данных
    size_t number_count;
    cin >> number_count;

    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cin >> bin_count;

    //Расчёт гистограммы
    const auto bins = make_histogram(numbers, bin_count);

    //Вывод данных
    show_histogram_text(bins);
}
