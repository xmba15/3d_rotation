# 3d_rotation #

## Rodrigues' rotation formula ##

A rotation can be represented by a rotation axis `n^` and an angle `θ`
<img src="https://render.githubusercontent.com/render/math?math=\omega=\hat{n}\theta">

A rotation matrix corresponding to a rotation by `θ` around an axis`n^` is as follows:

<img src="https://render.githubusercontent.com/render/math?math=R(\hat{n}, \theta) = \mathbf{I} + \sin{\theta}[\hat{n}]_{\times}+(1-\cos{\theta})[\hat{n}]^{2}_{\times}">

where `[n^]_x` is the matrix form of the cross product operator with the vector `n^=(n^_x,n^_y,n^_z)`
