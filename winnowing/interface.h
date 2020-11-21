#ifndef WINNOWING_INTERFACE_H
#define WINNOWING_INTERFACE_H

#include <string>
#include <vector>
#include <unordered_map>

class Winnowing {
  private:
    std::vector<std::pair<size_t, uint32_t>> hashes;
    std::unordered_map<uint32_t, std::vector<size_t>> hashes_map;

  public:
    Winnowing() = delete;
    explicit Winnowing(const std::string &contents);

  private:
    void record(uint32_t hash, size_t offset);

  public:
    size_t size() const;
    const std::vector<size_t> find(uint32_t hash) const; 
    static double match(const Winnowing *A, const Winnowing *B);
};

#endif//WINNOWING_INTERFACE_H
