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
    public SecurityFilterChain filterChain(HttpSecurity http) throws Exception {
        http
                .authorizeHttpRequests(auth -> auth
                        // 允许所有人访问登录页面和登录接口
                        .requestMatchers("/user/loginPage", "/user/login", "/login_page.html").permitAll()
                        // 其他所有请求需要认证
                        .anyRequest().authenticated()
                )
                // 关闭表单登录（因为你有自己的登录页面）
                .formLogin(form -> form.disable())
                // 关闭 CSRF（为了简化，开发时可以先关闭）
                .csrf(csrf -> csrf.disable());

        return http.build();
    }
}