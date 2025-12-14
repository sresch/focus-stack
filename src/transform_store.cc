#include <filesystem>
#include <string>
#include <iostream>

#include <opencv2/core/core.hpp>

#include "worker.hh"
#include "transform_store.hh"

using namespace focusstack;

Transform_Store::Transform_Store (std::shared_ptr<Logger> logger):
  m_logger (logger), m_directory (""), m_store_transform (false), m_load_transform (false)
{
}

void Transform_Store::set_store_transform (std::string path)
{
  m_store_transform = true;
  this->set_directory (path);
}

void Transform_Store::set_load_transform (std::string path)
{
  m_load_transform = true;
  this->set_directory (path);
}

void Transform_Store::store (std::shared_ptr<ImgTask> ref, cv::Mat transformation)
{
  if (m_logger->get_level() <= Logger::LOG_VERBOSE)
  {
    m_logger->verbose("transform store %s %s\n", this->get_file(ref->step()).c_str(), ref->step().c_str());
  }
  cv::FileStorage fs(this->get_file(ref->step()), cv::FileStorage::WRITE);
  fs.write("tr", transformation);
  fs.release();
}

void Transform_Store::load (std::shared_ptr<ImgTask> ref, cv::Mat tranformation)
{
  if (m_logger->get_level() <= Logger::LOG_VERBOSE)
  {
    m_logger->verbose("transform load %s %s\n", this->get_file(ref->step()).c_str(), ref->step().c_str());
  }
  cv::FileStorage fs(this->get_file(ref->step()), cv::FileStorage::READ);
  fs["tr"] >> tranformation;
  fs.release();
}

void Transform_Store::set_directory(std::string path)
{
  m_directory = path;
  if (!std::filesystem::is_directory(m_directory))
  {
    throw std::runtime_error("Directory '" + m_directory + "' provided for loading or storing transformations is not a valid directory.");
  }
}

std::string Transform_Store::get_file (std::string step)
{
    return m_directory + "/" + step + ".json";
}

