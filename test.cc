#include <gtest/gtest.h>

#include <iostream>

#include "3d_viewer_v2/model/interface/data_model.h"

const char *path = "./fortests.txt";
const double tolerance = 0.00001;

class TestModelViewerResult1 : public ::testing::Test {
 protected:
  void SetUp() {
    model = new s21::DataModel();
    model->LoadModel(path);
    model->MoveModel(1.5, 0, 0);
    model->MoveModel(0, 0.3, 0);
    model->MoveModel(0, 0, -1);
  }

  void TearDown() { delete model; }
  s21::DataModel *model;
};

TEST_F(TestModelViewerResult1, test1) {
  ASSERT_NEAR(model->GetObjectModel().Points()[0], 1.5, tolerance);
  ASSERT_NEAR(model->GetObjectModel().Points()[1], 0.3, tolerance);
  ASSERT_NEAR(model->GetObjectModel().Points()[2], -1, tolerance);
}

class TestModelViewerResult2 : public ::testing::Test {
 protected:
  void SetUp() {
    model = new s21::DataModel();
    model->LoadModel(path);
    model->ScaleModel(scale_factor);
  }

  void TearDown() { delete model; }
  s21::DataModel *model;
  double scale_factor = 15.5;
};

TEST_F(TestModelViewerResult2, test2) {
  ASSERT_NEAR(model->GetObjectModel().Points()[12], 7.75, tolerance);
  ASSERT_NEAR(model->GetObjectModel().Points()[13], 7.75, tolerance);
  ASSERT_NEAR(model->GetObjectModel().Points()[14], 15.5, tolerance);
}

class TestModelViewerResult3 : public ::testing::Test {
 protected:
  void SetUp() {
    for (int i = 0; i < s21::Object3D::Instance().GetPointsAmount(); ++i) {
      s21::Object3D::Instance().Points().at(i) = i + 3;
    }
    s21::Object3D::Instance().Rotate(1, 0, 0);
  }

  void TearDown() {}
  float result1[15] = {
      3.000000,  -2.046146, 6.067395,  6.000000,  -2.949652,
      10.212715, 9.000000,  -3.853158, 14.358035, 12.000000,
      -4.756664, 18.503356, 15.000000, -5.660170, 22.648675,
  };
};

TEST_F(TestModelViewerResult3, test3) {
  for (int i = 0; i < s21::Object3D::Instance().GetPointsAmount(); ++i) {
    ASSERT_NEAR(s21::Object3D::Instance().Points().at(i), result1[i],
                tolerance);
  }
}

class TestModelViewerResult4 : public ::testing::Test {
 protected:
  void SetUp() {
    for (int i = 0; i < s21::Object3D::Instance().GetPointsAmount(); ++i) {
      s21::Object3D::Instance().Points().at(i) = i + 3;
    }
    s21::Object3D::Instance().Rotate(0, 1, 0);
  }

  void TearDown() {}
  float result2[15] = {5.828262,  4.000000,  0.177099,  9.973582,  7.000000,
                       -0.726407, 14.118902, 10.000000, -1.629913, 18.264223,
                       13.000000, -2.533420, 22.409542, 16.000000, -3.436926};
};

TEST_F(TestModelViewerResult4, test4) {
  for (int i = 0; i < s21::Object3D::Instance().GetPointsAmount(); ++i) {
    ASSERT_NEAR(s21::Object3D::Instance().Points().at(i), result2[i],
                tolerance);
  }
}

class TestModelViewerResult5 : public ::testing::Test {
 protected:
  void SetUp() {
    for (int i = 0; i < s21::Object3D::Instance().GetPointsAmount(); ++i) {
      s21::Object3D::Instance().Points().at(i) = i + 3;
    }
    s21::Object3D::Instance().Rotate(0, 0, 1);
  }

  void TearDown() {}
  float result3[15] = {-1.744977, 4.685622,  5.000000,  -2.648483, 8.830942,
                       8.000000,  -3.551989, 12.976262, 11.000000, -4.455495,
                       17.121582, 14.000000, -5.359001, 21.266902, 17.000000};
};

TEST_F(TestModelViewerResult5, test5) {
  for (int i = 0; i < s21::Object3D::Instance().GetPointsAmount(); ++i) {
    ASSERT_NEAR(s21::Object3D::Instance().Points().at(i), result3[i],
                tolerance);
  }
}

class TestModelViewerResult6 : public ::testing::Test {
 protected:
  void SetUp() {
    model = new s21::DataModel();
    model->LoadModel(path);
    model->Normalize();
    model->ModelAlignmentCenter();
    result_name = model->GetFileName();
    result_path = model->GetFilePath();
    vertexes = model->GetNumberOfVertexes();
    ribs = model->GetNumberOfRibs();
    indices = model->GetNumberOfIndices();
  }

  void TearDown() { delete model; }
  s21::DataModel *model;
  std::string result_path;
  std::string result_name;
  int vertexes;
  int ribs;
  int indices;
};

TEST_F(TestModelViewerResult6, test6) {
  ASSERT_NEAR(model->GetObjectModel().Points()[12], 0, tolerance);
  ASSERT_NEAR(model->GetObjectModel().Points()[13], 0, tolerance);
  ASSERT_NEAR(model->GetObjectModel().Points()[14], 0.70710669, tolerance);
  ASSERT_EQ("fortests.txt", result_name);
  ASSERT_EQ(".", result_path);
  ASSERT_EQ(5, vertexes);
  ASSERT_EQ(7, ribs);
  ASSERT_EQ(22, indices);
}

class TestModelViewerResult7 : public ::testing::Test {
 protected:
  void SetUp() {
    model = new s21::DataModel();
    model->LoadModel(path);
    for (int i = 0; i < s21::Object3D::Instance().GetPointsAmount(); ++i) {
      s21::Object3D::Instance().Points().at(i) = i + 3;
    }
    model->RotateModel(0, 0, 1 * 180 / 3.14);
  }

  void TearDown() { delete model; }
  s21::DataModel *model;
  float result7[15] = {-1.744977, 4.685622,  5.000000,  -2.648483, 8.830942,
                       8.000000,  -3.551989, 12.976262, 11.000000, -4.455495,
                       17.121582, 14.000000, -5.359001, 21.266902, 17.000000};
};

TEST_F(TestModelViewerResult7, test7) {
  for (int i = 0; i < s21::Object3D::Instance().GetPointsAmount(); ++i) {
    ASSERT_NEAR(s21::Object3D::Instance().Points().at(i), result7[i],
                tolerance);
  }
}

class TestModelViewerResult8 : public ::testing::Test {
 protected:
  void SetUp() {
    model = new s21::DataModel();
    model->LoadModel(path);
    for (int i = 0; i < s21::Object3D::Instance().GetPointsAmount(); ++i) {
      s21::Object3D::Instance().Points().at(i) = i + 3;
    }
    model->RotateModel(0, 0, 1 * 180 / 3.14);
  }

  void TearDown() { delete model; }
  s21::DataModel *model;
  float result8[15] = {-1.744977, 4.685622,  5.000000,  -2.648483, 8.830942,
                       8.000000,  -3.551989, 12.976262, 11.000000, -4.455495,
                       17.121582, 14.000000, -5.359001, 21.266902, 17.000000};
};

TEST_F(TestModelViewerResult8, test8) {
  for (int i = 0; i < s21::Object3D::Instance().GetPointsAmount(); ++i) {
    ASSERT_NEAR(s21::Object3D::Instance().Points().at(i), result8[i],
                tolerance);
  }
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
