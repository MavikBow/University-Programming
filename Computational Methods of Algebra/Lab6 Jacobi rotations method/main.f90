! we work with the matrixA
! we transform it into A^T * A, don't aks me why.
! the method uses the Serial Jacobi rotations method with thresholds for symmetric matrices
! one iteratios goes like A_(k+1) = T_k^T * A_k * T_k.
! the very final A is a close to diagonal matrix with 
! eigenvalues of the original A on its diagonal,
! the product of all the T matrices (named matrixU here) 
! has the corresponding eigenvectors as its columns.

program Jacobi_rotations
    implicit none

    integer, parameter :: dp = selected_real_kind(15, 307)
    real(kind=dp), dimension(:,:), allocatable :: matrixA, matrixU, matrixA_safe
    real(kind=dp), dimension(:), allocatable :: sigma_vec, a_i_vec, a_j_vec
    real(kind=dp) :: cosin, sinus, temp, tau
    real(kind=dp), parameter :: Eps = 1.0E-15_dp
    integer :: inputFile, matrixSize, iteration_counter
    integer :: i, j

    inputFile = 1
    open(unit=inputFile, file='input.txt',status='unknown', action='read')
    read(inputFile, *) matrixSize

    allocate(matrixA_safe(matrixSize,matrixSize))
    allocate(matrixA(matrixSize,matrixSize))
    allocate(matrixU(matrixSize,matrixSize))
    allocate(sigma_vec(matrixSize))
    allocate(a_i_vec(matrixSize))
    allocate(a_j_vec(matrixSize))
   
    read(inputFile, *) (matrixA(i,:), i = 1, matrixSize)

    ! prep work

    matrixA = matmul(matrixA,transpose(matrixA))
    matrixA_safe = matrixA

    print '(A)', "inital matrix A'A"       
    do i = 1, matrixSize 
        print '(5(F14.8, 1X))', (matrixA(i,j), j = 1, matrixSize)
    end do

    sigma_vec = 0.0_dp
    do i = 1, matrixSize
        sigma_vec(i) = sum(matrixA(i,:)**2) - matrixA(i,i)**2
    end do

    matrixU = 0.0_dp
    forall(i = 1:matrixSize) matrixU(i,i) = 1.0_dp

    print '(A)', 'approximated number of iterations'
    print *, int((log10(Eps) - log10(sum(sigma_vec))) / log10(1.0_dp - 2.0_dp/(matrixSize*(matrixSize - 1))))

    iteration_counter = 0

    ! method starts

    do
        iteration_counter = iteration_counter + 1

    ! getting the i and j

        i = maxloc(sigma_vec,dim=1)
        a_i_vec = abs(matrixA(i,:))
        a_i_vec(i) = -1.0_dp
        j = maxloc(a_i_vec,dim=1)

    ! getting the sin and cos
        
        if(matrixA(i,i) == matrixA(j,j)) then
            cosin = sqrt(2.0_dp)/2.0_dp
            sinus = sqrt(2.0_dp)/2.0_dp
        else
            tau = (matrixA(i,i) - matrixA(j,j)) / (2.0_dp * matrixA(i,j))
            temp = sign(1.0_dp,tau) / (abs(tau) + sqrt(1.0_dp + tau**2))
            cosin = 1.0_dp / sqrt(1.0_dp + temp**2)
            sinus = temp * cosin
        end if

    ! B=AT

        a_i_vec = matrixA(:,i)
        a_j_vec = matrixA(:,j)
        matrixA(:,i) =  a_i_vec * cosin + a_j_vec * sinus
        matrixA(:,j) = -a_i_vec * sinus + a_j_vec * cosin

    ! U=UT
    
        a_i_vec = matrixU(:,i)
        a_j_vec = matrixU(:,j)
        matrixU(:,i) =  a_i_vec * cosin + a_j_vec * sinus
        matrixU(:,j) = -a_i_vec * sinus + a_j_vec * cosin

    ! A=T^T * B

        a_i_vec = matrixA(i,:)
        a_j_vec = matrixA(j,:)
        matrixA(i,:) =  a_i_vec * cosin + a_j_vec * sinus
        matrixA(j,:) = -a_i_vec * sinus + a_j_vec * cosin

    ! update the sigma_vec my way, damn it

        sigma_vec(i) = sum(matrixA(i,:)**2) - matrixA(i,i)**2
        sigma_vec(j) = sum(matrixA(j,:)**2) - matrixA(j,j)**2

    ! check the exit conditions

        if (abs(sum(sigma_vec)) <= Eps) exit

    end do

    ! method ends
    
    print '(A)', 'almost diagonal matrix A'       
    do i = 1, matrixSize 
        print '(5(F14.9, 1X))', (matrixA(i,j), j = 1, matrixSize)
    end do
    print '(A)', 'transformation matrix U'       
    do i = 1, matrixSize 
        print '(5(F14.9, 1X))', (matrixU(i,j), j = 1, matrixSize)
    end do

        print *, "this is iteration", iteration_counter

    ! calculating the discrepancy 

    ! r_i = A^T * A * x_1 - lambda_i * x_i
    print '(A)', 'discrepancies'       
    do i = 1, matrixSize
         print '(ES11.4)', maxval(abs(matmul(matrixA_safe,matrixU(:,i)) - matrixA(i,i) * matrixU(:,i)))
    end do

    close(inputFile) 

    deallocate(matrixA_safe)
    deallocate(matrixA)
    deallocate(matrixU)
    deallocate(sigma_vec)
    deallocate(a_i_vec)
    deallocate(a_j_vec)

end program Jacobi_rotations
