#include "YearDivider.h"
#include <iostream>
#include <filesystem>
#include <chrono>
#include <map>
using namespace std;

std::map<int, std::vector<std::filesystem::path>> filesByYear;


void YearDivider::TidyUp(std::string path) {
	CreateFile(path);
	SepareteYear(path);
}
void YearDivider::CreateFile(std::string path) {
    using namespace std::chrono;
    namespace fs = std::filesystem;

    for (const auto& entry : fs::directory_iterator(path)) {
        if (!fs::is_regular_file(entry)) continue;

        auto ftime = fs::last_write_time(entry); // ファイルの最終更新日時を取得
        auto sctp = time_point_cast<system_clock::duration>(
            ftime - fs::file_time_type::clock::now() + system_clock::now()
        );
        std::time_t cftime = system_clock::to_time_t(sctp);

        std::tm timeinfo;
        localtime_s(&timeinfo, &cftime);  // 安全なlocaltime_sに修正

        int year = 1900 + timeinfo.tm_year;

        filesByYear[year].push_back(entry.path());
    }
}
void YearDivider::SepareteYear(std::string path) {
    namespace fs = std::filesystem;
    for (const auto& [year, fileList] : filesByYear) {
        fs::path yearFolder = fs::path(path) / std::to_string(year);

        // 年フォルダがなければ作成
        if (!fs::exists(yearFolder)) {
            fs::create_directory(yearFolder);
        }

        for (const auto& file : fileList) {
            fs::path destination = yearFolder / file.filename();
            fs::copy_file(file, destination, fs::copy_options::skip_existing); // 上書きしない
        }
    }

}