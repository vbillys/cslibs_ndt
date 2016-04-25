#ifndef MATCHER_HPP
#define MATCHER_HPP
#include <memory>
#include <stdexcept>
#include <eigen3/Eigen/Geometry>

#include <ndt/data/pointcloud.hpp>
#include <ndt/grid/multi_grid.hpp>

namespace ndt {
namespace matching {
template<std::size_t Dim>
class Matcher {
public:
    typedef std::shared_ptr<Matcher>                     Ptr;
    typedef data::Pointcloud<Dim>                        PointCloudType;
    typedef std::array<double, Dim>                      ResolutionType;
    typedef Eigen::Transform<double, Dim, Eigen::Affine> TransformType;
    typedef Matcher<Dim>                                 BaseClass;

    struct Parameters {
        Parameters() :
            eps_rot(1e-6),
            eps_trans(1e-3),
            max_iterations(100)
        {
            resolution.fill(1.0);
        }
        Parameters(const ResolutionType &_resolution,
                   const double          _eps_rot,
                   const double          _eps_trans,
                   const std::size_t     _max_iterations) :
            resolution(_resolution),
            eps_rot(_eps_rot),
            eps_trans(_eps_trans),
            max_iterations(_max_iterations)
        {
        }

        ResolutionType          resolution;
        double                  eps_rot;
        double                  eps_trans;
        std::size_t             max_iterations;
    };



    Matcher(const Parameters &_params = Parameters()) :
        params(_params)
    {
    }

    inline virtual double match(const PointCloudType &_src,
                                const PointCloudType &_dst,
                                TransformType        &_transformation,
                                const TransformType  &_prior_transformation = TransformType::Identity()) = 0;

protected:
    Parameters                params;

    inline bool epsTrans(const double a,
                         const double b) const
    {
        return fabs(a - b) < params.eps_trans;
    }

    inline bool epsRot(const double a,
                       const double b) const
    {
        return fabs(a - b) < params.eps_rot;
    }

};
}
}
#endif // MATCHER_HPP
