// used to load or store transformation matrices

#pragma once

#include "logger.hh"

namespace focusstack {

class ImgTask;

class Transform_Store
{
public:
  Transform_Store(std::shared_ptr<Logger> logger);

  void set_store_transform (std::string path);
  void set_load_transform (std::string path);

  bool is_store_transform() const {return m_store_transform;};
  bool is_load_transform() const {return m_load_transform;};

  void load (std::shared_ptr<ImgTask> ref, cv::Mat tranformation);
  void store (std::shared_ptr<ImgTask> ref, cv::Mat tranformation);

private:
  std::shared_ptr<Logger> m_logger;
  std::string m_directory;
  bool m_store_transform;
  bool m_load_transform;

  void set_directory (std::string path);
  std::string get_file (std::string step);

};

}