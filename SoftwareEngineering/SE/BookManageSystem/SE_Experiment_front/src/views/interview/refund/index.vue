<template>
  <div>
    <el-row style="margin-top: 20px;">
      <el-col :span="12" :offset="6">
        <el-input placeholder="请输入关键字（支持模糊搜索）" v-model="keyword" class="input-with-select"
                  @keydown.enter.native="search">
          <el-button slot="append" icon="el-icon-search" @click="search"></el-button>
        </el-input>
      </el-col>
    </el-row>
    <el-row>
      <el-col :span="18" :offset="3" style="margin-top: 20px;">
        <el-table
          :data="tableData"
          border
          style="width: 100%">
          <el-table-column
            fixed
            prop="isbn"
            label="ISBN"
            width="150"
            align="center">
          </el-table-column>
          <el-table-column
            prop="userId"
            label="学号"
            align="center">
          </el-table-column>
          <el-table-column
            prop="name"
            label="退货人"
            width="150"
            align="center">
          </el-table-column>
          <el-table-column
            prop="num"
            label="退货数量"
            width="100"
            align="center">
          </el-table-column>
          <el-table-column
            prop="reason"
            label="退货原因"
            align="center">
          </el-table-column>
          <el-table-column
            prop="orderDate"
            label="订购日期"
            width="100"
            align="center">
          </el-table-column>
          <el-table-column
            prop="price"
            label="订购价格"
            width="100"
            align="center">
          </el-table-column>
        </el-table>
      </el-col>
    </el-row>
    <el-row style="margin-top: 20px;">
      <el-col :span="12" :offset="6">
        <el-pagination
          @size-change="handleSizeChange"
          @current-change="handleCurrentChange"
          :current-page="currentPage"
          :page-sizes="[5, 10, 30, 50]"
          :page-size="pageSize"
          layout="total, sizes, prev, pager, next, jumper"
          :total="total">
        </el-pagination>
      </el-col>
    </el-row>
  </div>
</template>

<script>

import {findAllRefund} from "@/api/refund";

export default {
  name: 'Interview-Refund',
  data() {
    return {
      loading: true,
      keyword: '',
      total: 0,
      currentPage: 1,
      pageSize: 10,
      tableData: []
    }
  },
  created() {
    this.search()
  },
  computed: {},
  methods: {
    search() {
      findAllRefund({
        all: this.keyword,
        page: this.currentPage - 1,
        size: this.pageSize
      }).then(response => {
        if (response.data != null) {
          this.tableData = response.data.content
          this.pageSize = response.data.pageable.pageSize
          this.currentPage = response.data.pageable.pageNumber + 1
          this.total = response.data.totalElements
        } else {
          this.tableData = []
          this.pageSize = 5
          this.currentPage = 1
          this.total = 0
        }
        this.loading = false
      })
    },
    handleClick(row) {
      console.log(row);
    },
    handleSizeChange(val) {
      this.pageSize = val
      this.search()
    },
    handleCurrentChange(val) {
      this.currentPage = val
      this.search()
    }
  }
}
</script>

<style lang="scss" scoped>

</style>
