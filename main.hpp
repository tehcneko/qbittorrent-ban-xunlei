#pragma once
#include <map>
#include <regex>

#define HOST "http://127.0.0.1:8080"
#define COOKIEFILE "./qbittorrent.cookie"

#define BANTIME 86400

std::regex ID_FILTER("-(XL|SD|XF|QD|BN|DL|TS|LT)(\\d+)-");
std::regex UA_FILTER(R"((\d+.\d+.\d+.\d+|cacao_torrent))");
std::regex PLAYER_FILTER("-(UW\\w{4}|SP(([0-2]\\d{3})|(3[0-5]\\d{2})))-");

std::regex regCOLON(":");

struct torrent_info {
  int num_leechs;
  uint64_t size;
};

static std::map<std::string, std::time_t> banned_list;
static std::map<std::string, struct torrent_info> torrent_list;

void do_job(CURL* curl);

// 清除过期封禁列表
void clear_expired_ban_list();

// 更新 Torrent 列表
void update_torrents(CURL* curl);


// 获取指定 Torrent 的 Peer 列表，并识别封禁
void update_peers(CURL* curl, const std::string&, const uint64_t&);

// 设置封禁列表
void set_ban_list(CURL* curl);

// CURL 读取数据处理函数
size_t CURL_write_stdString(void*, size_t, size_t, std::string*);
