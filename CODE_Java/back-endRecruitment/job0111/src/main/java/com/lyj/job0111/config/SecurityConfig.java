package com.lyj.job0111.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.web.SecurityFilterChain;

@Configuration
@EnableWebSecurity
public class SecurityConfig {
    @Bean
    public SecurityFilterChain filterChain(HttpSecurity http) {
        http
                .authorizeHttpRequests(authorize -> authorize
                        .requestMatchers("/user/loginPage", "/user/login","/login_page.html").permitAll()  //只有登录页和登录接口开放
                        .anyRequest().authenticated()                                    //其他都要登录
                )
                .csrf(csrf -> csrf.disable())//关掉CSRF
                .formLogin(form -> form.permitAll());  // 启用默认表单登录
        return http.build();
    }
}