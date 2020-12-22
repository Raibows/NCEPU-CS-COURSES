package com.example.backstage.Controller.InterviewController;

import com.alibaba.fastjson.JSONObject;
import com.example.backstage.Entity.InterviewEntity.Check;
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
* CheckController Tester. 
* 
* @author 罗驰
* @since <pre>6月 22, 2020</pre>
* @version 1.0 
*/
@RunWith(SpringRunner.class)
@SpringBootTest
@AutoConfigureMockMvc
public class CheckControllerTest {
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
* Method: addCheck(@RequestBody Check check) 
* 
*/ 
@Test
public void testAddCheck() throws Exception { 
//TODO: Test goes here...
    Check check = new Check("12","aef","201709000616","ae","1234567897777",10,"");
    String json= JSONObject.toJSONString(check);
    mvc.perform(MockMvcRequestBuilders.post("/check/addCheck")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: updateCheck(@RequestBody Check check) 
* 
*/ 
@Test
public void testUpdateCheck() throws Exception { 
//TODO: Test goes here...
    Check check = new Check("10000","清华大学出版社","201709000616","hero","9780062498531",10,"");
    String json= JSONObject.toJSONString(check);
    mvc.perform(MockMvcRequestBuilders.post("/check/updateCheck")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: addOrder(@RequestBody JSONObject object) 
* 
*/ 
@Test
public void testAddOrder() throws Exception { 
//TODO: Test goes here...
    String str="{\"all\":\"\",\"page\":0,\"size\":10}";
    mvc.perform(MockMvcRequestBuilders.post("/check/queryOrder")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(str)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 


} 
