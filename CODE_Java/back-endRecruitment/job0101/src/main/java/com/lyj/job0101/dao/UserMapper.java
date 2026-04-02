package com.lyj.job0101.dao;

import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import com.lyj.job0101.pojo.User;

@Mapper
public interface UserMapper {
    //实现查询功能
    @Select("select * from user where username=#{username}")
    User getUserByUsername(String username);
    //实现注册功能
    @Insert("insert into user (username,password) values (#{username},#{password})")
    void registerNewUser(String username,String password);
}
