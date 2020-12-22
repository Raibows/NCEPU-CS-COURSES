package com.example.test.mapper;

import com.example.test.bean.UserBean;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.springframework.stereotype.Component;
import org.springframework.stereotype.Repository;

@Repository
public interface UserMapper {

    @Select("select * from test.testuser where test.testuser.name = #{name} and test.testuser.password = #{password}; ")
    //boolean getInfo(String name , String password);
    UserBean getInfo(String name, String password);

}
