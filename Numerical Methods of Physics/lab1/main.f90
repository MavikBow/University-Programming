program bvp_solver
    implicit none

    integer, parameter :: dp = kind(0.0d0)
    integer, parameter :: N = 10!0
    real(dp), parameter :: kappa0 = 1.0_dp, g0 = 0.0_dp
    real(dp), parameter :: kappa1 = 1.0_dp, g1 = 0.0_dp
    
    real(dp) :: h, x(0:N), a(0:N), b(0:N), c(0:N), d(0:N), y(0:N)
    real(dp) :: kv(0:N), qv(0:N), fv(0:N), kp(0:N), ai(0:N)
    real(dp) :: k0, kN, kappa0_t, g0_t, kappa1_t, g1_t
    real(dp) :: d_0, d_N, phi_0, phi_N
    real(dp) :: d_i, phi_i
    real(dp) :: xrh, xlh
    real(dp) :: k_left_avg, k_right_avg, k_half_0, k_half_N
    integer :: i

    real(dp), parameter :: u_precise(0:10) = (/  0.1748246811329786_dp, & 
                                                0.1878037787771219_dp, &
                                                0.1935256875206210_dp, &
                                                0.1941513642936559_dp, &
                                                0.1913309366856842_dp, &
                                                0.1863145535959441_dp, &
                                                0.1800404444451557_dp, &
                                                0.1732047232006580_dp, &
                                                0.1663165908194967_dp, &
                                                0.1597418760886923_dp, &
                                                0.1537372782526116_dp /)

    real(dp), parameter :: U_VALS(0:100) = (/ &
        0.1748246811329786_dp, 0.1765234536916431_dp, 0.1781253538685278_dp, &
        0.1796334362523438_dp, 0.1810506774607439_dp, 0.1823799779695732_dp, &
        0.1836241639013564_dp, 0.1847859887738835_dp, 0.1858681352097715_dp, &
        0.1868732166078393_dp, 0.1878037787771219_dp, 0.1886623015343339_dp, &
        0.1894512002655695_dp, 0.1901728274530214_dp, 0.1908294741674690_dp, &
        0.1914233715272807_dp, 0.1919566921246587_dp, 0.1924315514198368_dp, &
        0.1928500091039205_dp, 0.1932140704310601_dp, 0.1935256875206210_dp, &
        0.1937867606299962_dp, 0.1939991393987098_dp, 0.1941646240644316_dp, &
        0.1942849666515143_dp, 0.1943618721326522_dp, 0.1943969995642506_dp, &
        0.1943919631960761_dp, 0.1943483335557511_dp, 0.1942676385086371_dp, &
        0.1941513642936559_dp, 0.1940009565355618_dp, 0.1938178212341866_dp, &
        0.1936033257311628_dp, 0.1933587996546153_dp, 0.1930855358423045_dp, &
        0.1927847912436932_dp, 0.1924577878014044_dp, 0.1921057133125145_dp, &
        0.1917297222701304_dp, 0.1913309366856842_dp, 0.1909104468923651_dp, &
        0.1904693123301087_dp, 0.1900085623125447_dp, 0.1895291967763077_dp, &
        0.1890321870130899_dp, 0.1885184763848272_dp, 0.1879889810223827_dp, &
        0.1874445905080961_dp, 0.1868861685425569_dp, 0.1863145535959441_dp, &
        0.1857305595442821_dp, 0.1851349762909419_dp, 0.1845285703737136_dp, &
        0.1839120855577754_dp, 0.1832862434148667_dp, 0.1826517438889746_dp, &
        0.1820092658488321_dp, 0.1813594676275237_dp, 0.1807029875494817_dp, &
        0.1800404444451558_dp, 0.1793724381536327_dp, 0.1786995500134705_dp, &
        0.1780223433420134_dp, 0.1773413639034427_dp, 0.1766571403658193_dp, &
        0.1759701847473582_dp, 0.1752809928521783_dp, 0.1745900446957688_dp, &
        0.1738978049203919_dp, 0.1732047232006580_dp, 0.1725112346394858_dp, &
        0.1718177601546713_dp, 0.1711247068562693_dp, 0.1704324684149974_dp, &
        0.1697414254218683_dp, 0.1690519457392406_dp, 0.1683643848434872_dp, &
        0.1676790861594705_dp, 0.1669963813870055_dp, 0.1663165908194967_dp, &
        0.1656400236549221_dp, 0.1649669782993410_dp, 0.1642977426630919_dp, &
        0.1636325944498492_dp, 0.1629718014386992_dp, 0.1623156217593942_dp, &
        0.1616643041609406_dp, 0.1610180882736725_dp, 0.1603772048649594_dp, &
        0.1597418760886923_dp, 0.1591123157286918_dp, 0.1584887294361764_dp, &
        0.1578713149614269_dp, 0.1572602623797788_dp, 0.1566557543120749_dp, &
        0.1560579661397040_dp, 0.1554670662143498_dp, 0.1548832160625709_dp, &
        0.1543065705853337_dp, 0.1537372782526116_dp  /)

    h = 1.0_dp / N
    do i = 0, N
        x(i) = real(i, dp) / N
    end do

    ! --- Method 1: Higher order approximation ---
    do i = 0, N
        kv(i) = k_func(x(i))
        qv(i) = q_func(x(i))
        fv(i) = f_func(x(i))
        kp(i) = kprime_func(x(i))
    end do

    do i = 1, N - 1
        a(i) = kv(i) / (h**2) - kp(i) / (2.0_dp * h)
        c(i) = kv(i) / (h**2) + kp(i) / (2.0_dp * h)
        b(i) = -(2.0_dp * kv(i) / (h**2) + qv(i))
        d(i) = -fv(i)
    end do

    k0 = k_func(0.0_dp)
    kN = k_func(1.0_dp)
    kappa0_t = kappa0 * (1.0_dp - h/2.0_dp * kp(0)/k0) + h/2.0_dp * qv(0)
    g0_t     = g0     * (1.0_dp - h/2.0_dp * kp(0)/k0) + h/2.0_dp * fv(0)
    kappa1_t = kappa1 * (1.0_dp + h/2.0_dp * kp(N)/kN) + h/2.0_dp * qv(N)
    g1_t     = g1     * (1.0_dp + h/2.0_dp * kp(N)/kN) + h/2.0_dp * fv(N)

    a(0) = 0.0;  b(0) = -k0/h - kappa0_t; c(0) = k0/h; d(0) = -g0_t
    a(N) = kN/h; b(N) = -kN/h - kappa1_t; c(N) = 0.0;  d(N) = -g1_t

    y = progonka(a, b, c, d, N)
    call print_sol(x, y, "Higher Order Approximation", N)


    ! --- Method 2: Integro-interpolation method ---
    do i = 1, N
        ai(i) = h / (exp(-x(i-1)) - exp(-x(i)))
    end do

    do i = 1, N - 1
    xlh = x(i) - h/2.0_dp
    xrh = x(i) + h/2.0_dp

    d_i = exp(xrh) - exp(xlh)
    phi_i = -(exp(-xrh) - exp(-xlh))

    a(i) = ai(i) / h
    c(i) = ai(i+1) / h
    b(i) = -( (ai(i) + ai(i+1))/h + d_i )
    d(i) = -phi_i
    end do

    ! --- Left Boundary (x=0) ---
    d_0 = exp(h/2.0_dp) - exp(0.0_dp)
    phi_0 = -(exp(-h/2.0_dp) - exp(0.0_dp))

    a(0) = 0.0
    b(0) = -(ai(1)/h + kappa0 + d_0)
    c(0) = ai(1)/h
    d(0) = -(g0 + phi_0)

    ! --- Right Boundary (x=1) ---
    d_N = exp(1.0_dp) - exp(1.0_dp - h/2.0_dp)
    phi_N = -(exp(-1.0_dp) - exp(-(1.0_dp - h/2.0_dp)))

    a(N) = ai(N)/h
    b(N) = -(ai(N)/h + kappa1 + d_N)
    c(N) = 0.0
    d(N) = -(g1 + phi_N)

    y = progonka(a, b, c, d, N)
    call print_sol(x, y, "Integro-interpolation Method", N)


    ! --- Method 3: Variational-Difference Method (Trapezoidal Rule) ---
    do i = 1, N - 1
        k_left_avg  = (k_func(x(i-1)) + k_func(x(i))) / 2.0_dp
        k_right_avg = (k_func(x(i)) + k_func(x(i+1))) / 2.0_dp

        a(i) = k_left_avg / (h**2) 
        c(i) = k_right_avg / (h**2)
        b(i) = -( (k_left_avg + k_right_avg)/(h**2) + q_func(x(i)) )
        d(i) = -f_func(x(i))
    end do

    k_half_0 = (k_func(x(0)) + k_func(x(1))) / 2.0_dp
    
    a(0) = 0.0
    b(0) = -( k_half_0/h + kappa0 + (h/2.0_dp)*q_func(x(0)) )
    c(0) = k_half_0/h
    d(0) = -( g0 + (h/2.0_dp)*f_func(x(0)) )

    k_half_N = (k_func(x(N-1)) + k_func(x(N))) / 2.0_dp
    
    a(N) = k_half_N/h
    b(N) = -( k_half_N/h + kappa1 + (h/2.0_dp)*q_func(x(N)) )
    c(N) = 0.0
    d(N) = -( g1 + (h/2.0_dp)*f_func(x(N)) )

    y = progonka(a, b, c, d, N)
    call print_sol(x, y, "Variational Method (Trapezoidal)", N)

contains

    function k_func(xx)
        real(dp) :: k_func, xx
        k_func = exp(xx)
    end function

    function q_func(xx)
        real(dp) :: q_func, xx
        q_func = exp(xx)
    end function

    function f_func(xx)
        real(dp) :: f_func, xx
        f_func = exp(-xx)
    end function

    function kprime_func(xx)
        real(dp) :: kprime_func, xx
        kprime_func = exp(xx)
    end function

    function progonka(a, b, c, d, n) result(x_sol)
        integer, intent(in) :: n
        real(dp), intent(in) :: a(0:n), b(0:n), c(0:n), d(0:n)
        real(dp) :: x_sol(0:n)
        real(dp) :: cp(0:n), dp_arr(0:n), denom
        integer :: i

        cp(0) = c(0) / b(0)
        dp_arr(0) = d(0) / b(0)

        do i = 1, n
            denom = b(i) - a(i) * cp(i-1)
            if (i /= n) then
                cp(i) = c(i) / denom
            else
                cp(i) = 0.0_dp
            end if
            dp_arr(i) = (d(i) - a(i) * dp_arr(i-1)) / denom
        end do

        x_sol(n) = dp_arr(n)
        do i = n-1, 0, -1
            x_sol(i) = dp_arr(i) - cp(i) * x_sol(i+1)
        end do
    end function

    subroutine print_sol(x_arr, y_arr, title, n)
        implicit none 
        integer, intent(in) :: n
        real(dp), intent(in) :: x_arr(0:n), y_arr(0:n)
        character(len=*), intent(in) :: title
        integer :: i
        real(dp) :: exact, err

        print *, "--- ", title, " ---"
        print *, 'i, x_arr(i), y_arr(i), err'
        do i = 0, n
        exact = u_precise(i)
        !exact = U_VALS(i)
        err = abs(y_arr(i) - exact)
        write(*, '(I6, F12.7, F20.10, ES20.10)') i, x_arr(i), y_arr(i), err
        end do
    end subroutine print_sol

end program bvp_solver
