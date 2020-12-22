package com.example.backstage.Controller.MaintainController;

import com.alibaba.fastjson.JSONObject;
import com.example.backstage.Entity.MaintainEntity.User;
import org.junit.Test;
import org.junit.Before; 
import org.junit.After; 
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultHandlers;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;

/** 
* UserController Tester. 
* 
* @author 罗驰
* @since <pre>6月 23, 2020</pre>
* @version 1.0 
*/
@RunWith(SpringRunner.class)
@SpringBootTest
@AutoConfigureMockMvc
public class UserControllerTest {
    @Autowired
    private MockMvc mvc;

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: addUser(@RequestBody User requestUser) 
* 
*/ 
@Test
public void testAddUser() throws Exception { 
//TODO: Test goes here...
    User user=new User("201709000123","周封","男","软件工程","软件1702","10005",10,"123",0,0);
    String json= JSONObject.toJSONString(user);
    mvc.perform(MockMvcRequestBuilders.post("/maintain/addUser")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();

} 

/** 
* 
* Method: updateUser(@RequestBody User user) 
* 
*/ 
@Test
public void testUpdateUser() throws Exception { 
//TODO: Test goes here...
    User user=new User("201709000123","周三封","男","软件工程","软件1702","10005",10,"123",0,0);
    String json= JSONObject.toJSONString(user);
    mvc.perform(MockMvcRequestBuilders.post("/maintain/updateUser")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: login(@RequestBody User requestUser) 
* 
*/ 
@Test
public void testLogin() throws Exception { 
//TODO: Test goes here...
    User user=new User();
    user.setId("201709000616");
    user.setPwd("luochi123");
    String json= JSONObject.toJSONString(user);
    mvc.perform(MockMvcRequestBuilders.post("/maintain/login")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: deleteUser(@RequestBody User user) 
* 
*/ 
@Test
public void testDeleteUser() throws Exception { 
//TODO: Test goes here...
    User user=new User();
    user.setId("201709000124");
    String json= JSONObject.toJSONString(user);
    mvc.perform(MockMvcRequestBuilders.post("/maintain/deleteUser")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: queryUserByName(@RequestBody JSONObject object) 
* 
*/ 
@Test
public void testQueryUserByName() throws Exception { 
//TODO: Test goes here...
    String str="{\"name\":\"\",\"page\":0,\"size\":10}";
    mvc.perform(MockMvcRequestBuilders.post("/maintain/queryUserByName")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(str)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: queryOverdu() 
* 
*/ 
@Test
public void testQueryOverdu() throws Exception { 
//TODO: Test goes here...
    mvc.perform(MockMvcRequestBuilders.post("/maintain/queryOverdue")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 


} 
