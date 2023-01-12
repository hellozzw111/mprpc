#include "mprpcconfig.h"

#include <iostream>
#include <string>

#include "yaml-cpp/yaml.h"

// 负责解析加载配置文件
void MprpcConfig::LoadConfigFile(const char *config_file)
{
    YAML::Node config = YAML::LoadFile(config_file);
    std::string name = config["name"].as<std::string>();
    std::string prefix_name = config["prefix_name"].as<std::string>();
    std::string role = config["role"].as<std::string>();
    YAML::Node ip_host = config["ip"][0];
    YAML::Node ip_zookeeper = config["ip"][0];
    YAML::Node port_host = config["port"][0];
    YAML::Node port_zookeeper = config["port"][0];
    std::string role = config["role"].as<std::string>();
    std::string name = config["name"].as<std::string>();
    std::string prefix_name = config["prefix_name"].as<std::string>();
    
    m_configMap.insert({"host_ip", ip_host["host"].as<std::string>()});
    m_configMap.insert({"host_port", port_host["host"].as<std::string>()});
    m_configMap.insert({"zookeeper_ip", ip_zookeeper["zookeeper"].as<std::string>()});
    m_configMap.insert({"zookeeper_host", port_zookeeper["zookeeper"].as<std::string>()});
    m_configMap.insert({"role", role});
    m_configMap.insert({"name", name});
    m_configMap.insert({"prefix_name", prefix_name});
    
}

// 查询配置项信息
std::string MprpcConfig::Load(const std::string &key)
{
    auto it = m_configMap.find(key);
    if (it == m_configMap.end())
    {
        return "";
    }
    return it->second;
}

// 去掉字符串前后的空格
void MprpcConfig::Trim(std::string &src_buf)
{
    int idx = src_buf.find_first_not_of(' ');
    if (idx != -1)
    {
        // 说明字符串前面有空格
        src_buf = src_buf.substr(idx, src_buf.size()-idx);
    }
    // 去掉字符串后面多余的空格
    idx = src_buf.find_last_not_of(' ');
    if (idx != -1)
    {
        // 说明字符串后面有空格
        src_buf = src_buf.substr(0, idx+1);
    }
}