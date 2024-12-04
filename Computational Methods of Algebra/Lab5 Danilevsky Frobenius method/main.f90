! we work with the matrixA
! we transform it into A^T * A, don't aks me why
! the method uses the Danilevsky method to get this new matrix
! into the Frobenius form.
! this way, the 1st row becomes the koefficients of the polynomial of matrix A^T*A

program Danilevsky
    implicit none

    integer, parameter :: dp = selected_real_kind(15, 307)
    real(kind=dp), dimension(:,:), allocatable :: matrixA, matrixB, matrixA_safe
    real(kind=dp), dimension(:), allocatable :: m_vector, m_vector_inv, lambdas
    real(kind=dp), parameter :: detA = 0.80343118688501101E-03_dp
    real(kind=dp) :: temp
    integer :: inputFile, matrixSize
    integer :: i, j, k

    inputFile = 1
    open(unit=inputFile, file='input.txt',status='unknown', action='read')
    read(inputFile, *) matrixSize

    allocate(matrixA_safe(matrixSize,matrixSize))
    allocate(matrixA(matrixSize,matrixSize))
    allocate(matrixB(matrixSize,matrixSize))
    allocate(m_vector(matrixSize))
    allocate(m_vector_inv(matrixSize))
    allocate(lambdas(matrixSize))
   
    read(inputFile, *) (matrixA(i,:), i = 1, matrixSize)

    ! prep work

    matrixA = matmul(matrixA,transpose(matrixA))
    matrixA_safe = matrixA

    print '(A)', "inital matrix A'A"       
    do i = 1, matrixSize 
        print '(5(F14.8, 1X))', (matrixA(i,j), j = 1, matrixSize)
    end do

    lambdas = (/ &
        0.5138612525621694_dp, &
        0.3948379287198427_dp, &
        0.2682915737385599_dp, &
        0.1721659914498502_dp, &
        0.0857293535295782_dp /)

    ! method starts

    do k = matrixSize - 1, 1, -1
        m_vector_inv = matrixA(k+1,:)
        m_vector = m_vector_inv / (-matrixA(k+1,k))
        m_vector(k) = 1_dp / matrixA(k+1,k)

        ! A = M^(-1) * A
        do j = 1, matrixSize
            matrixA(k,j) = dot_product(m_vector_inv,matrixA(:,j))
        end do

        ! B = A * M
        do i = 1, matrixSize
            do j = 1, k - 1
                matrixB(i,j) = matrixA(i,j) + matrixA(i,k) * m_vector(j)
            end do
            matrixB(i,k) = matrixA(i,k) * m_vector(k)
            do j = k + 1, matrixSize
                matrixB(i,j) = matrixA(i,j) + matrixA(i,k) * m_vector(j)
            end do
        end do

        matrixA = matrixB

    end do

    ! method ends

    print '(A)', 'Frobenius matrix A'       
    do i = 1, matrixSize 
        print '(5(F14.8, 1X))', (matrixA(i,j), j = 1, matrixSize)
    end do

    ! calculating the discrepancy 

    print '(A)', 'discrepancy of P_n(lambda_i)'       
    do i = 1, matrixSize
        temp = lambdas(i)**5
        do j = 1, matrixSize
            temp = temp - matrixA(1,j) * lambdas(i)**(matrixSize-j)
        end do 
        print '(ES11.4)', temp
    end do

    ! calculating the phi_1 and phi_n

    write(*,*)
    print '(A)', 'phi_1 = p_1 - Sp(A^T * A)'       
    temp = 0_dp
    do i = 1, matrixSize
        temp = temp + matrixA_safe(i,i)
    end do
    print '(ES11.4)', matrixA(1,1) - temp

    write(*,*)
    print '(A)', 'phi_n = p_n - det(A^T * A)'       
    print '(ES11.4)', matrixA(1,matrixSize) - detA

    close(inputFile) 

    deallocate(matrixA_safe)
    deallocate(matrixA)
    deallocate(matrixB)
    deallocate(m_vector)
    deallocate(m_vector_inv)
    deallocate(lambdas)

end program Danilevsky
