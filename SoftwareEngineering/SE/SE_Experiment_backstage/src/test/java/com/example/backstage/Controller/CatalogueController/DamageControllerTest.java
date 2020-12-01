package com.example.backstage.Controller.CatalogueController;

import com.alibaba.fastjson.JSONObject;
import com.example.backstage.Entity.CatalogueEntity.Damage;
import org.junit.Test;
import org.junit.Before; 
import org.junit.After;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.mock.web.MockRequestDispatcher;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultHandlers;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;

import java.math.BigDecimal;

/** 
* DamageController Tester. 
* 
* @author 罗驰
* @since <pre>6月 27, 2020</pre> 
* @version 1.0 
*/ 
@RunWith(SpringRunner.class)
@SpringBootTest
@AutoConfigureMockMvc
public class DamageControllerTest {
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
* Method: queryDamage(@RequestBody JSONObject object) 
* 
*/ 
@Test
public void testQueryDamage() throws Exception { 
//TODO: Test goes here...
       String str="{\"name\":\"c++\",\"page\":0,\"size\":10}";
       mvc.perform(MockMvcRequestBuilders.post("/damage/queryDamage")
               .contentType(MediaType.APPLICATION_JSON_UTF8)
               .content(str)
       ).andExpect(MockMvcResultMatchers.status().isOk())
               .andDo(MockMvcResultHandlers.print())
               .andReturn();
} 

/** 
* 
* Method: addDamage(@RequestBody Damage damage) 
* 
*/ 
@Test
public void testAddDamage() throws Exception { 
//TODO: Test goes here...
    Damage damage=new Damage();
    damage.setBookName("12");
    damage.setIsbn("1234567891345");
    damage.setChecker("罗驰");
    damage.setPrice(new BigDecimal(40));
    damage.setReason("123");
    damage.setState(false);
    String json=JSONObject.toJSONString(damage);
    mvc.perform(MockMvcRequestBuilders.post("/damage/addDamage")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: updateDamage(@RequestBody Damage damage) 
* 
*/ 
@Test
public void testUpdateDamage() throws Exception { 
//TODO: Test goes here...
    Damage damage=new Damage();
    damage.setBookName("Think Python");
    damage.setIsbn("9781491939369");
    damage.setChecker("罗驰");
    damage.setPrice(new BigDecimal(10));
    damage.setReason("书籍大量损坏");
    damage.setState(false);
    String json=JSONObject.toJSONString(damage);
    mvc.perform(MockMvcRequestBuilders.post("/damage/updateDamage")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: deleteDamage(@RequestBody Damage damage) 
* 
*/ 
@Test
public void testDeleteDamage() throws Exception { 
//TODO: Test goes here...
    Damage damage=new Damage();
    damage.setIsbn("9787302145509");
    String json=JSONObject.toJSONString(damage);
    mvc.perform(MockMvcRequestBuilders.post("/damage/deleteDamage")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 


} 
